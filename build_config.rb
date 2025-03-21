MRuby::Build.new do |conf|
  toolchain :clang
  enable_debug

  conf.gembox 'full-core'
  conf.gem File.expand_path(File.dirname(__FILE__))
  conf.gem core: "mruby-sprintf" # Not sure why this is necessary as it's already in the full-core gembox
  conf.enable_test
  conf.compilers.each do |c|
    c.defines += %w(MRB_UTF8_STRING)
  end

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.compilers.each do |c|
      c.defines += %w(MRB_USE_DEBUG_HOOK)
    end
  end
end
