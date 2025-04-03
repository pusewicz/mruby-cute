MRuby::Build.new do |conf|
  toolchain :clang

  conf.gembox "full-core"

  conf.gem __dir__
  conf.gem core: "mruby-sprintf" # Not sure why this is necessary as it's already in the full-core gembox

  conf.compilers.each do |c|
    c.defines += %w[MRB_UTF8_STRING]
  end

  if ENV["DEBUG"] == "true"
    conf.enable_test
    conf.enable_debug
    conf.compilers.each do |c|
      c.defines += %w[MRB_USE_DEBUG_HOOK]
      c.flags << "-O0"
      c.flags << "-g"
      c.flags << "-g3"
      c.flags << "-glldb"
    end
  elsif ENV["RELEASE"] == "true"
    # Release flags
    spec.compilers.each do |c|
      c.flags << "-O3"
      c.flags << "-DNDEBUG"
    end
  end
end
