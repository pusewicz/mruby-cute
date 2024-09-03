assert("cf_result_success") do
  assert_kind_of(Object, Cute.result_success)
end

assert("cf_result_error") do
  assert_kind_of(Object, Cute.result_error("details"))
end

assert("cf_is_error") do
  error = Cute.result_error("details")
  assert_true(Cute.is_error(error))

  success = Cute.result_success
  assert_false(Cute.is_error(success))
end
