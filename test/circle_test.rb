assert("Cute::Circle#new") do
  position = Cute::V2.new(10, 20)
  circle = Cute::Circle.new(position, 30)

  assert_equal(10, circle.position.x)
  assert_equal(20, circle.position.y)
  assert_float(30.0, circle.radius)
end

assert("Cute::Circle setters") do
  position = Cute::V2.new(10, 20)
  circle = Cute::Circle.new(position, 30)

  # Test position setter
  new_position = Cute::V2.new(15, 25)
  circle.position = new_position
  assert_equal(15, circle.position.x)
  assert_equal(25, circle.position.y)

  # Test radius setter
  circle.radius = 35
  assert_float(35.0, circle.radius)
end

assert("Cute::Circle factory method") do
  position = Cute::V2.new(10, 20)
  circle = Cute::Circle(position, 30)

  assert_equal(10, circle.position.x)
  assert_equal(20, circle.position.y)
  assert_float(30.0, circle.radius)
end

# assert("Cute::Circle#to_s and #inspect") do
#   position = Cute::V2.new(10, 20)
#   circle = Cute::Circle.new(position, 30)

#   # Just check that these methods work without asserting format
#   to_s_result = circle.to_s
#   assert_true(to_s_result.is_a?(String))

#   inspect_result = circle.inspect
#   assert_true(inspect_result.is_a?(String))
# end
