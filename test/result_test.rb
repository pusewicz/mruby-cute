assert("cf_is_error") do
  error = Cute.cf_result_error("Error message")
  assert_true(Cute.cf_is_error(error))

  success = Cute.cf_result_success
  assert_false(Cute.cf_is_error(success))
end
