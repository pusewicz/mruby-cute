require 'etc'
require 'rake/clean'

CMAKE_BUILD_PARALLEL_LEVEL=ENV.fetch('CMAKE_BUILD_PARALLEL_LEVEL', Etc.nprocessors + 2)
MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "cute_build_config.rb")
MRUBY_VERSION="3.3.0"
CUTE_VERSION="master"

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

task :example => :compile do
  exec "mruby/build/host/bin/mruby example/example.rb"
end

task :default => :compile
