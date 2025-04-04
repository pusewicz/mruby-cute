assert("Cute::Aabb") do
  v1 = Cute::V2(1, 2)
  v2 = Cute::V2(3, 4)
  aabb = Cute::Aabb.new(v1, v2)
  assert_equal(v1, aabb.min)
  assert_equal(v2, aabb.max)
end

assert("Cute::Aabb dereferenced owner") do
  v1 = Cute::V2(1, 2)
  v2 = Cute::V2(3, 4)
  aabb = Cute::Aabb.new(v1, v2)

  min = aabb.min
  max = aabb.max
  aabb = nil
  GC.start
  assert_equal(v1, min)
  assert_equal(v2, max)
end
