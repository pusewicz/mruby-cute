MRuby::Build.new do |conf|
  toolchain :clang
  conf.gembox 'default'
  conf.gem '../mruby-cute'
  conf.enable_test

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'

    # Debug flags
    conf.cc.flags << "-g3"
    conf.cc.flags << "-Wno-unused-parameter"
    conf.cc.flags << "-Wno-unused-variable"
    conf.cc.flags << "-Wno-unused-function"
    conf.cc.flags << "-Wno-unused-value"
  end
end
