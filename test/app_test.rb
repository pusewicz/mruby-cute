assert("cf_make_app") do
  assert_kind_of(Object, Cute.make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app"))
  assert_nil(Cute.app_destroy)
end

assert("cf_app_is_running") do
  assert_true(Cute.app_is_running)
end

assert("cf_make_app CF_AppOptionFlagBits") do
  assert_equal(1 << 0, Cute::APP_OPTIONS_NO_GFX_BIT)
  assert_equal(1 << 1, Cute::APP_OPTIONS_FULLSCREEN_BIT)
  assert_equal(1 << 2, Cute::APP_OPTIONS_RESIZABLE_BIT)
  assert_equal(1 << 3, Cute::APP_OPTIONS_HIDDEN_BIT)
  assert_equal(1 << 4, Cute::APP_OPTIONS_WINDOW_POS_CENTERED_BIT)
  assert_equal(1 << 5, Cute::APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT_BIT)
  assert_equal(1 << 6, Cute::APP_OPTIONS_NO_AUDIO_BIT)
  assert_equal(1 << 7, Cute::APP_OPTIONS_GFX_D3D11_BIT)
  assert_equal(1 << 8, Cute::APP_OPTIONS_GFX_D3D12_BIT)
  assert_equal(1 << 9, Cute::APP_OPTIONS_GFX_METAL_BIT)
  assert_equal(1 << 10, Cute::APP_OPTIONS_GFX_VULKAN_BIT)
end

assert("cf_default_display") do
  assert_equal(0, Cute.default_display)
end
