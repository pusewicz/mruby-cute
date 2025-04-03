require 'yard'
require 'yard/rake/yardoc_task'
require 'etc'
require 'rake/clean'

ENV["CMAKE_GENERATOR"] ||= "Ninja"
ENV["CMAKE_BUILD_PARALLEL_LEVEL"] ||= (Etc.nprocessors + 2).to_s
ENV["DEBUG"] ||= "true"

MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "build_config.rb")
MRUBY_VERSION="3.3.0"
CUTE_VERSION="1.1.0"
DEPS_DIR=File.expand_path('deps')
MRUBY_DEPS_DIR=File.join(DEPS_DIR, 'mruby')
MRUBY_ARCHIVE=File.join(DEPS_DIR, "mruby-#{MRUBY_VERSION}.zip")
CUTE_DEPS_DIR=File.join(DEPS_DIR, 'cute_framework')
CUTE_BUILD_DIR=File.join(CUTE_DEPS_DIR, ['build', ENV["CMAKE_GENERATOR"], ENV["RELEASE"] ? "release" : "debug"].join("_"))
CUTE_ARCHIVE=File.join(DEPS_DIR, "cute_framework-#{CUTE_VERSION}.zip")

directory DEPS_DIR

CLOBBER.include(MRUBY_DEPS_DIR)

YARD::Rake::YardocTask.new do |t|
  t.files = ['docstub/**/*.rb', 'mrblib/**/*.rb']
end

desc "Download MRuby"
file MRUBY_ARCHIVE => [DEPS_DIR] do
  url = "https://github.com/mruby/mruby/archive/refs/tags/#{MRUBY_VERSION}.zip"
  sh "curl -L #{url} -o #{MRUBY_ARCHIVE}"
end

desc "Extract MRuby"
file MRUBY_DEPS_DIR => [MRUBY_ARCHIVE] do
  sh "unzip -q #{MRUBY_ARCHIVE} -d #{DEPS_DIR}"
  sh "mv #{DEPS_DIR}/mruby-#{MRUBY_VERSION} #{MRUBY_DEPS_DIR}"
end

desc "Download Cute"
file CUTE_ARCHIVE => [DEPS_DIR] do
  url = "https://github.com/RandyGaul/cute_framework/archive/refs/tags/#{CUTE_VERSION}.zip"
  sh "curl -L #{url} -o #{CUTE_ARCHIVE}"
end

desc "Extract Cute"
file CUTE_DEPS_DIR => [CUTE_ARCHIVE] do
  sh "unzip -q #{CUTE_ARCHIVE} -d #{DEPS_DIR}"
  sh "mv #{DEPS_DIR}/cute_framework-#{CUTE_VERSION} #{CUTE_DEPS_DIR}"
end

file CUTE_BUILD_DIR => CUTE_DEPS_DIR do
  mkdir_p CUTE_BUILD_DIR
  cd CUTE_BUILD_DIR do
    cmake_flags = {
      "CMAKE_BUILD_TYPE" => ENV["RELEASE"] ? "Release" : "Debug",
      "CF_FRAMEWORK_BUILD_SAMPLES" => "OFF",
      "CF_FRAMEWORK_BUILD_TESTS" => "OFF",
      "CMAKE_EXPORT_COMPILE_COMMANDS" => "ON",
    }
    sh "cmake #{cmake_flags.map { |k, v| "-D#{k}=#{v}"}.join(' ')} .."
    sh "cmake --build ."
  end
end

task :compile_cute => [CUTE_BUILD_DIR] do
  cd CUTE_BUILD_DIR do
    sh "cmake --build ."
  end
end

desc "compile binary"
task :compile => [CUTE_BUILD_DIR, MRUBY_DEPS_DIR] do
  cd MRUBY_DEPS_DIR do
    sh "env MRUBY_CONFIG=#{MRUBY_CONFIG} rake all"
  end
end

desc "test"
task :test => [CUTE_BUILD_DIR, MRUBY_DEPS_DIR] do
  cd MRUBY_DEPS_DIR do
    sh "env MRUBY_CONFIG=#{MRUBY_CONFIG} rake all test"
  end
end

desc "REPL"
task :repl => :compile do
  exec "#{MRUBY_DEPS_DIR}/build/host/bin/mirb"
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

task :default => :test
