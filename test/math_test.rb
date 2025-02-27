assert("Cute::CF_V2") do
  v = Cute.V2(3.0, 4.0)
  assert_kind_of(Cute::V2, v)
  assert_equal(3.0, v.x)
  assert_equal(4.0, v.y)
end
