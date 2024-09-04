assert("Cute::Result#initialize") do
  result = Cute::Result.new(0, "Success")
  assert_equal(0, result.code)
  assert_equal("Success", result.details)

  result = Cute::Result.new(0)
  assert_equal(0, result.code)
  assert_nil(result.details)

  result = Cute::Result.new(0, nil)
  assert_equal(0, result.code)
  assert_nil(result.details)
end

assert("Cute::Result#error?") do
  result = Cute::Result.new(0, "Success")
  assert_false(result.error?)

  result = Cute::Result.new(-1, "Error")
  assert_true(result.error?)
end

assert("cf_is_error") do
  result = Cute::Result.new(0, "Success")
  assert_false(Cute.is_error(result))

  result = Cute::Result.new(-1, "Error")
  assert_true(Cute.is_error(result))
end
