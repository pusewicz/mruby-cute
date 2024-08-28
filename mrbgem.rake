MRuby::Gem::Specification.new("mruby-cute") do |spec|
  spec.license = "MIT"
  spec.authors = "pusewicz"
  spec.summary = "mruby bindings for the Cute game library"

  cc.include_paths << File.expand_path("../cute_framework/include")
  cc.include_paths << File.expand_path("../cute_framework/libraries")
  cxx.include_paths << File.expand_path("../cute_framework/include")

  puts "cc.include_paths: #{cc.include_paths}"
  # cc.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
  # cxx.defines.push("GOSU_FFI_EXPORTS", "GOSU_DEPRECATED=")
  # cc.flags << "/std:c++11"
  # cxx.flags << "/std:c++11"

  linker.library_paths << File.expand_path("../cute_framework/build")
  linker.libraries.push("physfs", "cute")
end
