assert("SinCos initialization without params") do
  # Default initialization
  v = Cute::SinCos.new
  assert_kind_of(Cute::SinCos, v)
  assert_equal(0.0, v.s.round(2))
  assert_equal(1.0, v.c.round(2))
end

assert("SinCos initialization with params") do
  # Initialization with radians
  v = Cute::SinCos.new(Math::PI / 2.0)
  assert_kind_of(Cute::SinCos, v)
  assert_equal(1.0, v.s.round(2))
  assert_equal(0.0, v.c.round(2))
end

assert("SinCos factory method") do
  v = Cute.SinCos(Math::PI / 2.0)
  assert_kind_of(Cute::SinCos, v)
  assert_equal(1.0, v.s.round(2))
  assert_equal(0.0, v.c.round(2))
end

assert("SinCos accessors") do
  v = Cute::SinCos.new(Math::PI / 2.0)
  assert_equal(1.0, v.s.round(2))
  assert_equal(0.0, v.c.round(2))

  v.s = -1.0
  v.c = 0.0
  assert_equal(-1.0, v.s.round(2))
  assert_equal(0.0, v.c.round(2))
end

assert("SinCos to_s and inspect") do
  v = Cute::SinCos.new(Math::PI / 2)
  assert_equal("SinCos(s=1.000 c=-0.000)", v.to_s)
  assert_match('#<Cute::SinCos:0x* s=1.000 c=-0.000>', v.inspect)
end
