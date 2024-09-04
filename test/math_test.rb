assert("Cute::V2") do
  v = Cute::V2.new(3.0, 4.0)
  assert_kind_of(Cute::V2, v)
  assert_equal(3.0, v.x)
  assert_equal(4.0, v.y)

  v.x = 5.0
  v.y = 6.0
  assert_equal(5.0, v.x)
  assert_equal(6.0, v.y)

  v2 = Cute::V2.new(1.0, 2.0)
  result = v + v2
  assert_kind_of(Cute::V2, result)
  assert_equal(6.0, result.x)
  assert_equal(8.0, result.y)
end
