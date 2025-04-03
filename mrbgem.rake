require_relative "mrblib/version"

MRuby::Gem::Specification.new("mruby-cute") do |spec|
  spec.license = "MIT"
  spec.authors = "pusewicz"
  spec.summary = "mruby bindings for the Cute game library"
  spec.version = Cute::VERSION
  spec.add_dependency "mruby-sprintf"
  spec.add_dependency "mruby-math"

  if ENV['DEBUG'] == 'true'
    # Debug flags
    spec.compilers.each do |c|
      c.defines += %w(MRB_USE_DEBUG_HOOK)
      c.flags << "-O0"
      c.flags << "-g"
      c.flags << "-g3"
      c.flags << "-glldb"
    end
  elsif ENV['RELEASE'] == 'true'
    # Release flags
    spec.compilers.each do |c|
      c.flags << "-O3"
      c.flags << "-DNDEBUG"
    end
  end

  # General flags
  spec.compilers.each do |c|
    c.include_paths << File.expand_path("../cute_framework/include")
    c.include_paths << File.expand_path("../cute_framework/libraries")
  end

  # C flags
  spec.cc.flags << "-std=c2x"

  # C++ flags
  spec.cxx.flags << "-std=c++17"

  # Linker flags
  static_libs = Dir.glob(File.expand_path("../cute_framework/build*/**/*.a"))

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
