assert("cf_make_app") do
  assert_kind_of(Object, Cute.make_app("test_app"))
  assert_nil(Cute.app_destroy)
end

assert("cf_app_is_running") do
  assert_true(Cute.app_is_running)
end
