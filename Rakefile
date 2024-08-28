require 'etc'

CMAKE_BUILD_PARALLEL_LEVEL=ENV.fetch('CMAKE_BUILD_PARALLEL_LEVEL', Etc.nprocessors + 2)
MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "cute_build_config.rb")
MRUBY_VERSION="3.3.0"
CUTE_VERSION="master"

file :mruby do
  cmd = "git clone --depth=1 https://github.com/mruby/mruby.git"
  if MRUBY_VERSION != 'master'
    cmd << " && cd mruby"
    cmd << " && git fetch --tags && git checkout $(git rev-parse #{MRUBY_VERSION})"
  end
  sh cmd
end

file :cute_framework do
  cmd = "git clone --depth=1 https://github.com/RandyGaul/cute_framework.git"
  if CUTE_VERSION != 'master'
    cmd << " && cd cute_framework"
    cmd << " && git fetch --tags && git checkout $(git rev-parse #{CUTE_VERSION})"
  end
  sh cmd
  sh "cd cute_framework && mkdir build && cd build && cmake -G Ninja .. && CMAKE_BUILD_PARALLEL_LEVEL=#{CMAKE_BUILD_PARALLEL_LEVEL} cmake --build ."
end

desc "compile binary"
task :compile => [:cute_framework, :mruby] do
  sh "cd mruby && MRUBY_CONFIG=#{MRUBY_CONFIG} rake all"
end

desc "test"
task :test => [:cute_framework, :mruby] do
  sh "cd mruby && MRUBY_CONFIG=#{MRUBY_CONFIG} rake all test"
end

desc "cleanup"
task :clean do
  exit 0 unless File.directory?('mruby')
  sh "cd mruby && rake deep_clean"
end

task :default => :compile
