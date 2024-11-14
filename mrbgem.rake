require_relative "mrblib/version"

MRuby::Gem::Specification.new("mruby-cute") do |spec|
  spec.license = "MIT"
  spec.authors = "pusewicz"
  spec.summary = "mruby bindings for the Cute game library"
  spec.version = Cute::VERSION

  if ENV['DEBUG']
    # Debug flags
    spec.cc.flags << "-g3"
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

  spec.linker.flags += static_libs.map { |lib| "-Wl,-rpath,#{File.dirname(lib)}" }.uniq
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
      spec.linker.flags << "-Wl,-framework,#{framework}"
    end
  end
end
