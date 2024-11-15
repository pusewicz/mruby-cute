assert("CF_KeyButton constants") do
  assert_equal(0, Cute::CF_KEY_UNKNOWN)
  assert_equal(32, Cute::CF_KEY_SPACE)
  keys = %w[a b c d e f g h i j k l m n o p q r s t u v w x y z]
  i = 0
  while i < keys.size
    assert_equal(i + 97, Cute.const_get("CF_KEY_#{keys[i].upcase}"))
    i += 1
  end
end

assert("cf_key_down") do
  assert_equal(false, Cute.cf_key_down(Cute::CF_KEY_A))
end

assert("cf_key_up") do
  assert_equal(true, Cute.cf_key_up(Cute::CF_KEY_A))
end

assert("cf_key_just_pressed") do
  assert_equal(false, Cute.cf_key_just_pressed(Cute::CF_KEY_A))
end

assert("cf_key_just_released") do
  assert_equal(false, Cute.cf_key_just_released(Cute::CF_KEY_A))
end

assert("cf_key_repeating") do
  assert_equal(false, Cute.cf_key_repeating(Cute::CF_KEY_A))
end

assert("cf_clear_key_states") do
  assert_nil Cute.cf_clear_key_states
end
