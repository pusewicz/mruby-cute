require 'etc'
require 'json'
require 'rake/clean'

CMAKE_BUILD_PARALLEL_LEVEL=ENV.fetch('CMAKE_BUILD_PARALLEL_LEVEL', Etc.nprocessors + 2)
MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "cute_build_config.rb")
MRUBY_VERSION="3.3.0"
CUTE_VERSION="master"
AST_FILE = "cute.json"
MAPPING_FILE = "mapping.json"

desc "Clone MRuby"
file :mruby do
  cmd = "git clone --depth=1 https://github.com/mruby/mruby.git"
  if MRUBY_VERSION != 'master'
    cmd << " && cd mruby"
    cmd << " && git fetch --tags && git checkout $(git rev-parse #{MRUBY_VERSION})"
  end
  sh cmd
end

desc "Clone and build Cute Framework"
task :cute_framework do
  unless File.directory?('cute_framework')
    cmd = "git clone --depth=1 https://github.com/RandyGaul/cute_framework.git"
    if CUTE_VERSION != 'master'
      cmd << " && cd cute_framework"
      cmd << " && git fetch --tags && git checkout $(git rev-parse #{CUTE_VERSION})"
    end
    sh cmd
  end

  unless File.directory?('cute_framework/build')
    sh "cd cute_framework && mkdir build && cd build && cmake -G Ninja .. && CMAKE_BUILD_PARALLEL_LEVEL=#{CMAKE_BUILD_PARALLEL_LEVEL} cmake --build ."
  end
end
CLEAN.include('cute_framework/build')

desc "compile binary"
task :compile => [:cute_framework, :mruby] do
  sh "cd mruby && env MRUBY_CONFIG=#{MRUBY_CONFIG} DEBUG=true rake all"
end

desc "test"
task :test => [:cute_framework, :mruby] do
  sh "cd mruby && env MRUBY_CONFIG=#{MRUBY_CONFIG} DEBUG=true rake all test"
end

task :deep_clean do
  if File.directory?('mruby')
    sh "cd mruby && rake deep_clean"
  end
end
Rake::Task[:clean].enhance [:deep_clean]

task :generate => [:dump_ast] do
  gen = Generate.new(AST_FILE, MAPPING_FILE)
  File.write("src/generated.c", gen.generate)
end

task :dump_ast do
  # Use clang to dump AST as JSON for cute
  sh "cd cute_framework && clang -Iinclude -Ilibraries -Xclang -ast-dump=json include/cute.h > ../cute.json"
end

class Generate
  def initialize(ast_file, mapping_file)
    @json = JSON.parse(File.read(ast_file))
    @mapping = JSON.parse(File.read(mapping_file))
    @bindings = []
    @function_names = []
    @allowed_functions = @mapping.values.flatten
  end

  def traverse(node)
    case node
    when Hash
      if node['kind'] == 'FunctionDecl' && node['name']
        func, name = generate_mrb_function(node)
        if @allowed_functions.include?(name)
          puts "Generating binding for #{name}"
          @bindings << func
          @function_names << name
        end
      end
      node.values.each { |v| traverse(v) }
    when Array
      node.each { |item| traverse(item) }
    end
  end

  def generate
    traverse(@json)

    header = <<~HEADER
      #include "mruby-cute.h"
      #include <cute.h>
      #include <mruby.h>
    HEADER

    init_func = <<~INIT
      void mrb_cute_generated_init(mrb_state* mrb, struct RClass* mrb_cute_module)
      {
        #{@function_names.map { |name| "DEFINE_MODULE_FUNCTION(#{name.delete_prefix("cf_")}, MRB_ARGS_NONE());" }.join("\n")}
      }
    INIT

    [header, @bindings.join("\n"), init_func].join("\n")
  end

  def generate_mrb_function(func_decl)
    name = func_decl['name']
    return_type = func_decl['type']['qualType']
    params = func_decl['inner']&.select { |p| p['kind'] == 'ParmVarDecl' } || []

    param_types = params.map { |p| p['type']['qualType'] }

    mrb_func = <<~FUNC
      static mrb_value mrb#{name}(mrb_state *mrb, mrb_value self)
      {
        // TODO: Implement argument parsing based on #{param_types}
        // TODO: Call C function and convert result
        #{return_type} result = #{name}();
        return mrb_nil_value();
      }
    FUNC

    [mrb_func, name]
  end
end

task :default => :compile
