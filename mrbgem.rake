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
  spec.linker.libraries.push(
    "SDL3",
    "SPIRV",
    "SPIRV-Tools",
    "SPIRV-Tools-opt",
    "spirv-cross-c",
    "spirv-cross-core",
    "spirv-cross-glsl",
    "spirv-cross-msl",
    "c++",
    "cute",
    "glslang",
    "glslang-default-resource-limits",
    "objc",
    "physfs",
  )
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
