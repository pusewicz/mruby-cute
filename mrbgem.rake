require_relative "mrblib/version"

MRuby::Gem::Specification.new("mruby-cute") do |spec|
  spec.license = "MIT"
  spec.authors = "pusewicz"
  spec.summary = "mruby bindings for the Cute game library"
  spec.version = Cute::VERSION

  spec.cc.flags << "-std=c99"

  if ENV['DEBUG'] == 'true'
    # Debug flags
    spec.cc.flags << "-g3"
    spec.cc.flags << "-Wno-unused-parameter"
    spec.cc.flags << "-Wno-unused-variable"
    spec.cc.flags << "-Wno-unused-function"
    spec.cc.flags << "-Wno-unused-value"
  end

  spec.cc.include_paths << File.expand_path("../cute_framework/include")
  spec.cc.include_paths << File.expand_path("../cute_framework/libraries")
  spec.cxx.flags << "-std=c++17"
  spec.cxx.include_paths << File.expand_path("../cute_framework/include")

  spec.linker.library_paths << File.expand_path("../cute_framework/build")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/_deps/sdl3-build")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/_deps/spirv_cross-build")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/glslang")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/glslang/OSDependent/Unix")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/SPIRV")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source/opt")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source/link")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source/lint")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source/diff")
  spec.linker.library_paths << File.expand_path("../cute_framework/build/glslang-build/External/spirv-tools/source/reduce")
  spec.linker.libraries.push(
    "c++",
    "physfs",
    "SDL_uclibc", # TODO: Maybe for Linux only?
    "SDL3",
    "GenericCodeGen",
    "SPIRV-Tools",
    "SPIRV-Tools-opt",
    "SPIRV-Tools-link",
    "SPIRV-Tools-lint",
    "SPIRV-Tools-diff",
    "SPIRV-Tools-reduce",
    "glslang-default-resource-limits",
    "OSDependent",
    "SPVRemapper",
    "spirv-cross-core",
    "spirv-cross-glsl",
    "spirv-cross-msl",
    "spirv-cross-c",
    "MachineIndependent",
    "glslang",
    "SPIRV",
    "cute",
  )

  if /linux/ =~ RUBY_PLATFORM
    spec.linker.libraries.push(
      "spirv-cross-hlsl",
    )
  end
  if /darwin/ =~ RUBY_PLATFORM
    spec.linker.libraries.unshift("objc")
    %w[
      AVFoundation
      AudioToolbox
      Cocoa
      Carbon
      CoreAudio
      CoreMedia
      CoreVideo
      CoreHaptics
      ForceFeedback
      Foundation
      GameController
      UniformTypeIdentifiers
      IOKit
      Metal
      QuartzCore
    ].each do |framework|
      spec.linker.flags << "-framework #{framework}"
    end
  end
end
