assert("cf_make_app") do
  result = Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  assert_kind_of(Cute::CF_Result, result)
  assert_false(Cute.cf_is_error(result))
  assert_nil(Cute.cf_app_destroy)
end

assert("cf_app_is_running") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  assert_true(Cute.cf_app_is_running)
  assert_nil(Cute.cf_app_destroy)
end

assert("cf_make_app CF_AppOptionFlagBits") do
  assert_equal(1 << 0, Cute::CF_APP_OPTIONS_NO_GFX_BIT)
  assert_equal(1 << 1, Cute::CF_APP_OPTIONS_FULLSCREEN_BIT)
  assert_equal(1 << 2, Cute::CF_APP_OPTIONS_RESIZABLE_BIT)
  assert_equal(1 << 3, Cute::CF_APP_OPTIONS_HIDDEN_BIT)
  assert_equal(1 << 4, Cute::CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT)
  assert_equal(1 << 5, Cute::CF_APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT_BIT)
  assert_equal(1 << 6, Cute::CF_APP_OPTIONS_NO_AUDIO_BIT)
  assert_equal(1 << 7, Cute::CF_APP_OPTIONS_GFX_D3D11_BIT)
  assert_equal(1 << 8, Cute::CF_APP_OPTIONS_GFX_D3D12_BIT)
  assert_equal(1 << 9, Cute::CF_APP_OPTIONS_GFX_METAL_BIT)
  assert_equal(1 << 10, Cute::CF_APP_OPTIONS_GFX_VULKAN_BIT)
end

assert("cf_default_display") do
  assert_equal(0, Cute.cf_default_display)
end
