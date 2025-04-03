assert("V2 initialization") do
  # Default initialization
  v = Cute::V2.new
  assert_kind_of(Cute::V2, v)
  assert_equal(0.0, v.x)
  assert_equal(0.0, v.y)

  # Initialization with coordinates
  v = Cute::V2.new(3.5, 4.5)
  assert_equal(3.5, v.x)
  assert_equal(4.5, v.y)
end

assert("V2 factory method") do
  v = Cute.V2(3.0, 4.0)
  assert_kind_of(Cute::V2, v)
  assert_equal(3.0, v.x)
  assert_equal(4.0, v.y)
end

assert("V2 accessors") do
  v = Cute::V2.new(3.0, 4.0)
  assert_equal(3.0, v.x)
  assert_equal(4.0, v.y)

  v.x = 5.5
  v.y = 6.5
  assert_equal(5.5, v.x)
  assert_equal(6.5, v.y)
end

assert("V2 to_s and inspect") do
  v = Cute::V2.new(3.0, 4.0)
  assert_equal("V2(3.000, 4.000)", v.to_s)
  assert_match("#<Cute::V2:0x* x=3.000 y=4.000>", v.inspect)
end
