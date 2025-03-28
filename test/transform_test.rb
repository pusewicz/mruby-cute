assert("Transform initialization without params") do
  v = Cute::Transform.new
  assert_kind_of(Cute::Transform, v)
  assert_kind_of(Cute::SinCos, v.r)
  assert_kind_of(Cute::V2, v.p)
  assert_equal(0.0, v.r.s.round(2))
  assert_equal(1.0, v.r.c.round(2))
  assert_equal(0.0, v.p.x)
  assert_equal(0.0, v.p.y)
end

assert("Transform initialization with params") do
  v = Cute::Transform.new(Cute::V2(2.0, 3.0), Math::PI / 2.0)
  assert_kind_of(Cute::Transform, v)
  assert_kind_of(Cute::SinCos, v.r)
  assert_kind_of(Cute::V2, v.p)
  assert_equal(1.0, v.r.s.round(2))
  assert_equal(0.0, v.r.c.round(2))
  assert_equal(2.0, v.p.x)
  assert_equal(3.0, v.p.y)
end

assert("Transform factory method") do
  v = Cute::Transform()
  assert_kind_of(Cute::Transform, v)
  assert_kind_of(Cute::SinCos, v.r)
  assert_kind_of(Cute::V2, v.p)
  assert_equal(0.0, v.r.s.round(2))
  assert_equal(1.0, v.r.c.round(2))
  assert_equal(0.0, v.p.x)
  assert_equal(0.0, v.p.y)
end

assert("Transform factory method with params") do
  v = Cute::Transform(Cute::V2(2.0, 3.0), Math::PI / 2.0)
  assert_kind_of(Cute::Transform, v)
  assert_kind_of(Cute::SinCos, v.r)
  assert_kind_of(Cute::V2, v.p)
  assert_equal(1.0, v.r.s.round(2))
  assert_equal(0.0, v.r.c.round(2))
  assert_equal(2.0, v.p.x)
  assert_equal(3.0, v.p.y)
end

assert("Transform accessors") do
  v = Cute::Transform.new
  assert_equal(0.0, v.r.s.round(2))
  assert_equal(1.0, v.r.c.round(2))
  assert_equal(0.0, v.p.x)
  assert_equal(0.0, v.p.y)

  v.p = Cute::V2(5.5, 6.5)
  assert_equal(5.5, v.p.x)
  assert_equal(6.5, v.p.y)

  v.r = Cute::SinCos(Math::PI / 2)
  assert_equal(1.0, v.r.s.round(2))
  assert_equal(0.0, v.r.c.round(2))
end
