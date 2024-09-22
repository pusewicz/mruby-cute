require_relative "mrblib/version"

MRuby::Gem::Specification.new("mruby-cute") do |spec|
  spec.license = "MIT"
  spec.authors = "pusewicz"
  spec.summary = "mruby bindings for the Cute game library"
  spec.version = Cute::VERSION

  if ENV['DEBUG'] == 'true'
    # Debug flags
    spec.cc.flags << "-g3"
    spec.cc.flags << "-Wno-unused-parameter"
    spec.cc.flags << "-Wno-unused-variable"
    spec.cc.flags << "-Wno-unused-function"
    spec.cc.flags << "-Wno-unused-value"
  end

  # C flags
  spec.cc.flags << "-std=c99"
  spec.cc.include_paths << File.expand_path("../cute_framework/include")
  spec.cc.include_paths << File.expand_path("../cute_framework/libraries")

  # C++ flags
  spec.cxx.flags << "-std=c++17"
  spec.cxx.include_paths << File.expand_path("../cute_framework/include")

  # Linker flags
  static_libs = Dir.glob(File.expand_path("../cute_framework/build/**/*.a"))
  spec.linker.library_paths += static_libs.map { |lib| File.dirname(lib) }.uniq
  spec.linker.libraries.push("c++")
  spec.linker.libraries += static_libs.map { |lib| File.basename(lib, ".a").sub(/^lib/, "") }

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
