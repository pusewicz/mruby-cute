MRuby::Build.new do |conf|
  toolchain :clang
  conf.gembox 'default'
  conf.gem '../mruby-cute'
  conf.enable_test

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.gem core: 'mruby-bin-debugger'
    conf.cc.defines = %w(MRB_USE_DEBUG_HOOK)
  end
end
