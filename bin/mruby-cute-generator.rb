#!/usr/bin/env ruby
# mruby-cute-generator.rb - Generate MRuby bindings for CuteFramework

require "fileutils"
require "debug"

class String
  def indent(n)
    lines = self.split("\n")
    lines.map { |line| " " * n + line }.join("\n")
  end
end

class CuteBindingGenerator
  attr_reader :header_content, :enums, :functions, :structs

  class Header
    attr_reader :filename, :path

    def initialize(path:)
      @filename = File.basename(path)
      @path = path
      @content = nil
    end

    def content
      @content ||= File.read(@path).gsub(/CF_API\s+/, "").gsub(/CF_INLINE\s+/, "").gsub(/CF_CALL\s+/, "").tap do |content|
        puts "Read content from #{@path}"
        puts content
      end
    end

    def scan(pattern, &block)
      content.scan(pattern, &block)
    end

    def <=>(other)
      @filename <=> other.filename
    end
  end

  class Collection < Array
    def filter_by_header(header)
      filter { it[:header] == header }
    end

    def to_s(level = 0)
      map { |it| it.to_s(level) }.join("\n")
    end
  end

  class Enum < Struct.new(:name, :values, :header)
    def to_s
      <<~ENUM
        typedef enum #{name}
        {
          #{values.map { |val| "#{val[:name]} = #{val[:value]}" }.join(",\n  ")}
        } #{name};
      ENUM
    end
  end

  class EnumDef < Struct.new(:name, :value, :header)
    def to_s
      <<~ENUM_DEF
        #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
        #{name}
        #undef CF_ENUM
      ENUM_DEF
    end
  end

  class Function < Struct.new(:name, :return_type, :params, :description, :header)
    def to_wrapper_s
      wrapper = <<~WRAPPER
        /* #{description} */
        static mrb_value mrb_#{name}(mrb_state *mrb, mrb_value self) {
      WRAPPER

      # Add parameter extraction
      if params.empty?
        wrapper += "  // No parameters\n"
      else
        wrapper += "  mrb_value #{params.map { |p| p[:name] }.join(", ")};\n\n"

        # Generate the correct number of arguments for the get_args call
        args_format = params.map { |_| "o" }.join("")
        args_list = params.map { |p| "&#{p[:name]}" }.join(", ")

        wrapper += "  mrb_get_args(mrb, \"#{args_format}\", #{args_list});\n\n"

        # Convert MRuby values to C types
        params.each do |param|
          wrapper += "  #{param[:type]} c_#{param[:name]} = #{mrb_to_type(param[:type], param[:name])};\n"
        end
        wrapper += "\n"
      end

      # Call the actual function
      if return_type == "void"
        wrapper += "  #{name}(#{params.map { |p| "c_#{p[:name]}" }.join(", ")});\n"
        wrapper += "  return mrb_nil_value();\n"
      else
        wrapper += "  #{return_type} result = #{name}(#{params.map { |p| "c_#{p[:name]}" }.join(", ")});\n"
        wrap_type = type_to_mrb(return_type)
        wrapper += case wrap_type 
        when "mrb_float_value", "mrb_cptr_value"
          "  return #{wrap_type}(mrb, result);\n"
        else
          "  return #{wrap_type}(result);\n"
        end
      end

      wrapper += "}"
      wrapper
    end

    def to_s
      <<~FUNCTION
        // #{description}
        #{return_type} #{name}(#{params.map { |p| "#{p[:type]} #{p[:name]}" }.join(", ")});
      FUNCTION
    end

    def to_static_function_declaration_s
      "static mrb_value mrb_#{name}(mrb_state *mrb, mrb_value self);"
    end

    def to_function_assignment_s
      "mrb_define_module_function(mrb, mCute, \"#{name}\", mrb_#{name}, MRB_ARGS_REQ(#{params.size}));"
    end

    private
  FIXNUM_VALUES = %w[bool int int32_t uint32_t CF_DisplayID uint8_t uint64_t CF_AppOptionFlags]

  def type_to_mrb(c_type)
    case c_type.strip
    when *FIXNUM_VALUES
      "mrb_fixnum_value"
    when "float", "double"
      "mrb_float_value"
    when "const char*", "char*"
      "mrb_str_new_cstr"
    when /CF_(\w+)/
      "mrb_cptr_value" # TODO: Convert struct to MRuby value
    else
      # Handle pointers and other types
      if c_type.include?("*")
        "mrb_cptr_value" # Convert pointers to MRuby CData
      else
        puts "WARN: Unknown type: `#{c_type}'"
        "mrb_fixnum_value /* TODO: Unknown type `#{c_type}' */" # Default to int for unknown types
      end
    end
  end

  def mrb_to_type(c_type, var_name)
    case c_type.strip
    when "bool"
      "mrb_bool(#{var_name})"
    when *FIXNUM_VALUES
      "mrb_fixnum(#{var_name})"
    when "float", "double"
      "mrb_float(#{var_name})"
    when "const char*", "char*"
      "mrb_str_to_cstr(mrb, #{var_name})"
    when /CF_(\w+)/
      "mrb_cptr(#{var_name})" # TODO: Convert MRuby value to struct
    else
      # Handle pointers and other types
      if c_type.include?("*")
        "mrb_cptr(#{var_name})" # Convert MRuby CData to pointer
      else
        puts "WARN: Unknown type: `#{c_type}' for variable `#{var_name}'"
        "mrb_fixnum(#{var_name}) /* TODO: Unknown type `#{c_type}' */" # Default to int for unknown types
      end
    end
  end

  end

  class Struct < Struct.new(:name, :fields, :header)
    def to_s
      %Q(static const struct mrb_data_type #{name}_type = { "#{name}", mrb_free };)
    end

    def to_data_get_function_s
      downcase_name = name.downcase
      <<~GET_FUNC
        #{name}* mrb_#{downcase_name}_get_ptr(mrb_state* mrb, mrb_value self)
        {
            mrb_#{downcase_name}_data_t* data = (mrb_#{downcase_name}_data_t*) DATA_PTR(self);
            return data->#{downcase_name}_ptr;
        }
      GET_FUNC
    end
  end

  def initialize(paths)
    @headers = paths.map { |path| Header.new(path: path) }
    @enums = Collection.new
    @enum_defs = Collection.new
    @functions = Collection.new
    @structs = Collection.new

    # Output directories
    @out_dir = File.expand_path(File.join(File.dirname(__FILE__), ".."))
    @src_dir = File.join(@out_dir, "src")
    @dst = File.join(@src_dir, "cute.c")

    puts "Generating MRuby bindings for CuteFramework..."
    @headers.each do |header|
      puts "Using header: #{header.filename}"
    end
  end

  def parse
    parse_enums
    parse_structs
    parse_functions
  end

  def parse_enums
    # Pattern to match enum definitions
    enum_pattern = /typedef\s+enum\s+(\w+)\s*\{([^}]+)\}\s*(\w+);/m

    @headers.each do |header|
      # Find all enums
      header.scan(enum_pattern) do |enum_name, enum_content, typedef_name|
        puts "Found enum: #{typedef_name}"
        enum_values = []

        # Extract enum values - handle the CF_ENUM macro pattern
        if enum_content.include?("CF_ENUM")
          enum_content.scan(/(CF_(\w+)_DEFS)/) do |key, value|
            @enum_defs << EnumDef.new(name: key, value: value, header: header)
          end
        else
          # Handle regular enum definitions
          enum_content.scan(/(\w+)\s*=\s*([^,]+)/) do |name, value|
            enum_values << {name: name, value: value.strip, header: header}
          end
          @enums << Enum.new(name: typedef_name, values: enum_values, header: header)
        end
      end
    end
  end

  def parse_structs
    # Pattern to match struct definitions
    struct_pattern = /typedef\s+(?:struct|union)\s+(\w+)\s*\{((?:[^{}]|(?:\{[^{}]*\}))*)\}\s*(\w+);/m

    @headers.each do |header|
      header.scan(struct_pattern) do |struct_name, struct_content, typedef_name|
        puts "Found struct: #{typedef_name}"
        fields = []

        # Extract struct fields
        struct_content.scan(/\/\*\s*@member\s+(.*?)\*\/\s*([^;]+);/m) do |comment, field_def|
          field_name = field_def.strip.split.last.gsub(/[\[\]]/, "")
          field_type = field_def.strip.split(field_name).first.strip

          fields << {
            name: field_name,
            type: field_type,
            comment: comment.strip,
            header: header
          }
        end

        @structs << Struct.new(
          name: typedef_name,
          fields: fields,
          header: header
        )
      end
    end
  end

  def parse_functions
    # Pattern to match function declarations
    function_pattern = /
      [^#\*]                   # Skip preprocessor directives and comments
      ^(?!define\s*)           # Skip #define
      (?<return_type>\w+\*?)\s*# Return type
      (?<function_name>cf_\w+) # Function name
      \((?<arguments>(.*?))\)  # Arguments
      (?:\s*\{.*\})?           # Function body
    /x

    @headers.each do |header|
      header.scan(function_pattern) do |return_type, func_name, params|
        next unless func_name.start_with?("cf_")
        next if return_type == "return"

        puts "Found function: `#{func_name}' with return type `#{return_type}' and params `#{params}'"

        parameters = []
        if params.strip != "void" && !params.empty?
          params.split(",").each do |param|
            param = param.strip
            if param =~ /\A(?<type>\w+(?:\s+\w+)*(?:\s*\*)*)\s+(?<name>\w+)\z/
              param_name = $2
              param_type = $1
              parameters << {name: param_name, type: param_type}
            end
          end
        end

        # Look for documentation
        doc_pattern = /\/\*\*\s*\n\s*\*\s*@function\s+#{func_name}\s*\n([\s\S]*?)\*\//m
        description = ""
        if @header_content =~ doc_pattern
          doc_content = $1
          description_pattern = /\*\s*@brief\s+([\s\S]*?)(\n\s*\*\s*@|\n\s*\*\/)/m
          if doc_content =~ description_pattern
            description = $1.strip.gsub(/\n\s*\*\s*/, " ")
          end
        end

        @functions << Function.new(
          name: func_name,
          return_type: return_type,
          params: parameters,
          description: description,
          header: header
        )
      end
    end
  end

  def generate_source_files
    FileUtils.mkdir_p(@src_dir)

    generate_modules
    generate_module_init
  end

  def generate_modules
    # Generate one source file per header and include only the source for those
    @headers.each do |header|
      dst = File.join(@src_dir, header.filename.gsub(".h", ".c"))
      content = <<~CODE
        /**
         * Generated on #{Time.now}
         */

        #include "cute.h"
        #include \<#{header.filename}\>

        /**
         * Struct definitions
         */
        #{generate_struct_definitions(header)}

        /**
         * Data type definitions
         */
        #{generate_data_type_definitions(header)}

        /**
         * Function wrapper declarations TODO: Move to header
         */
        #{generate_function_wrapper_declarations(header)}

        /**
         * Function wrappers
         */
        #{generate_function_wrappers(header)}
        #{generate_data_get_functions(header)}

        /**
         * Initialize the module
         */
        void mrb_mruby_cute_#{header.filename.gsub(".h", "")}_gem_init(mrb_state *mrb, struct RClass *mCute)
        {
          // Define enums
          #{generate_enum_assignments(header).indent(2)[2..]}

          // Define enum def definitions
          #{generate_enum_defs_definitions(header).indent(2)[2..]}

          // Define functions
          #{generate_function_assignments(header).indent(2)[2..]}
        }
      CODE
      puts "Generated #{dst}"
      File.write(dst, content)
    end
  end

  def generate_module_init
    content = <<~CODE
      /**
        * Generated on #{Time.now}
        */

      // Include CuteFramework headers
      #{@headers.sort.map { |header| "#include \<#{header.filename}\>" }.join("\n")}

      #include "cute.h"

      // Class/module definitions
      static struct RClass *mCute;

      // Initialize the module
      void mrb_mruby_cute_gem_init(mrb_state *mrb)
      {
        // Create Cute module
        mCute = mrb_define_module(mrb, "Cute");

        // Initialize submodules
        #{generate_submodule_inits.indent(2)[2..]}
      }

      // Cleanup
      void mrb_mruby_cute_gem_final(mrb_state *mrb) {
        // Nothing to clean up
      }
    CODE

    puts "Generated #{@dst}"
    File.write(@dst, content)
  end

  def generate_submodule_inits
    @headers.map { |header| "void mrb_mruby_cute_#{header.filename.gsub(".h", "")}_gem_init(mrb_state *mrb, struct RClass *mCute);" }.join("\n")
  end

  def generate_data_type_definitions(header)
    # typedef struct mrb_cf_sprite_data_t
    # {
    #   CF_Sprite* cf_sprite_ptr;
    # } mrb_cf_sprite_data_t;
    @structs.filter_by_header(header).map do |struct|
      struct_name = struct.name
      downcase_name = struct_name.downcase
      <<~TYPEDEF
        typedef struct mrb_#{downcase_name}_data_t {
          #{struct_name}* #{downcase_name}_ptr;
        } mrb_#{downcase_name}_data_t;
      TYPEDEF
    end.join("\n")
  end

  def generate_struct_definitions(header)
    @structs.filter_by_header(header).map(&:to_s).join("\n")
  end

  def generate_enum_assignments(header)
    assignments = []

    @enums.each do |enum|
      enum[:values].each do |val|
        assignments << "mrb_define_const(mrb, mCute, \"#{val[:name]}\", mrb_fixnum_value(#{val[:value]}));"
      end
    end

    assignments.join("\n")
  end

  def generate_enum_defs_definitions(header)
    @enum_defs.filter_by_header(header).map(&:to_s).join("\n")
  end

  def generate_function_wrappers(header)
    @functions.filter_by_header(header).sort_by(&:name).map(&:to_wrapper_s).join("\n")
  end

  def generate_function_wrapper_declarations(header)
    @functions.filter_by_header(header).sort_by(&:name).map(&:to_static_function_declaration_s).join("\n")
  end

  def generate_data_get_functions(header)
    @structs.filter_by_header(header).map(&:to_data_get_function_s).join("\n")
  end

  def generate_function_assignments(header)
    @functions.filter_by_header(header).sort_by(&:name).map(&:to_function_assignment_s).join("\n")
  end

  def generate
    parse
    generate_source_files

    puts "Generated MRuby bindings for CuteFramework in #{@out_dir}/"
    puts "Found #{@enums.size} enums, #{@structs.size} structs, and #{@functions.size} functions."
  end
end

header_paths = %w[
  cute_app.h
  cute_color.h
  cute_math.h
].map { |path| File.expand_path(File.join(File.dirname(__FILE__), "../deps/cute_framework", "include", path)) }

generator = CuteBindingGenerator.new(header_paths)
generator.generate
