MRuby::Build.new do |conf|
  toolchain :clang
  enable_debug

  conf.gembox 'full-core'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.enable_test

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_USE_DEBUG_HOOK)
  end
end
