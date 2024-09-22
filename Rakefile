require 'etc'
require 'rake/clean'

ENV["CMAKE_GENERATOR"] ||= "Ninja"
ENV["CMAKE_BUILD_PARALLEL_LEVEL"] ||= (Etc.nprocessors + 2).to_s
MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "cute_build_config.rb")
MRUBY_VERSION="3.3.0"
CUTE_VERSION="sdl3-fetch-http"
DEPS_DIR=File.expand_path('deps')
MRUBY_DEPS_DIR=File.join(DEPS_DIR, 'mruby')
CUTE_DEPS_DIR=File.join(DEPS_DIR, 'cute_framework')
CUTE_BUILD_DIR=File.join(CUTE_DEPS_DIR, 'build')

directory DEPS_DIR

CLEAN.include(CUTE_BUILD_DIR)
CLOBBER.include(MRUBY_DEPS_DIR)

desc "Clone MRuby"
file MRUBY_DEPS_DIR => [DEPS_DIR] do
  url = "https://github.com/mruby/mruby/archive/refs/tags/#{MRUBY_VERSION}.zip"
  sh "curl -L #{url} -o #{DEPS_DIR}/mruby.zip"
  sh "unzip -q #{DEPS_DIR}/mruby.zip -d #{DEPS_DIR}"
  sh "mv #{DEPS_DIR}/mruby-#{MRUBY_VERSION} #{MRUBY_DEPS_DIR}"
  rm "#{DEPS_DIR}/mruby.zip"
end

desc "Clone and build Cute Framework"
file CUTE_DEPS_DIR => [DEPS_DIR] do
  url = "https://github.com/bullno1/cute_framework/archive/refs/heads/#{CUTE_VERSION}.zip"
  unless File.directory?(CUTE_DEPS_DIR)
    sh "curl -L #{url} -o #{DEPS_DIR}/cute_framework.zip"
    sh "unzip -q #{DEPS_DIR}/cute_framework.zip -d #{DEPS_DIR}"
    sh "mv #{DEPS_DIR}/cute_framework-#{CUTE_VERSION} #{CUTE_DEPS_DIR}"
    rm "#{DEPS_DIR}/cute_framework.zip"
  end

  unless File.directory?(CUTE_BUILD_DIR)
    mkdir_p CUTE_BUILD_DIR
    cd CUTE_BUILD_DIR do
      sh "cmake -G Ninja -DCF_FRAMEWORK_BUILD_SAMPLES=OFF -DCF_FRAMEWORK_BUILD_TESTS=OFF .. && cmake --build ."
    end
  end
end

desc "compile binary"
task :compile => [CUTE_DEPS_DIR, MRUBY_DEPS_DIR] do
  cd MRUBY_DEPS_DIR do
    sh "env MRUBY_CONFIG=#{MRUBY_CONFIG} DEBUG=true rake all"
  end
end

desc "test"
task :test => [CUTE_DEPS_DIR, MRUBY_DEPS_DIR] do
  cd MRUBY_DEPS_DIR do
    sh "env MRUBY_CONFIG=#{MRUBY_CONFIG} DEBUG=true rake all test"
  end
end

task :deep_clean do
  if File.directory?(MRUBY_DEPS_DIR)
    cd MRUBY_DEPS_DIR do
      sh "rake deep_clean"
    end
  end
end
Rake::Task[:clean].enhance [:deep_clean]

task :example => :compile do
  exec "#{MRUBY_DEPS_DIR}/build/host/bin/mruby example/example.rb"
end

task :default => :compile
