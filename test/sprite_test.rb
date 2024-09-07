assert("cf_sprite_defaults") do
  sprite = Cute.cf_sprite_defaults
  assert_kind_of(Cute::CF_Sprite, sprite)
  assert_equal(0, Cute.cf_sprite_width(sprite))
  assert_equal(0, Cute.cf_sprite_height(sprite))
end

assert("cf_sprite_width") do
  sprite = Cute.cf_sprite_defaults
  assert_equal(0, Cute.cf_sprite_width(sprite))
end

assert("cf_sprite_height") do
  sprite = Cute.cf_sprite_defaults
  assert_equal(0, Cute.cf_sprite_height(sprite))
end

assert("cf_make_demo_sprite") do
  Cute.make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  sprite = Cute.cf_make_demo_sprite
  assert_kind_of(Cute::CF_Sprite, sprite)
end

assert("cf_sprite_is_playing") do
  sprite = Cute.cf_make_demo_sprite
  assert_false(Cute.cf_sprite_is_playing(sprite, "idle"))
  assert_false(Cute.cf_sprite_is_playing(sprite, "walk"))
end

assert("cf_sprite_play") do
  sprite = Cute.cf_make_demo_sprite
  assert_nil(Cute.cf_sprite_play(sprite, "idle"))
  assert_true(Cute.cf_sprite_is_playing(sprite, "idle"))
end

assert("cf_sprite_update") do
  sprite = Cute.cf_make_demo_sprite
  assert_nil(Cute.cf_sprite_update(sprite))
end

assert("cf_sprite_draw") do
  sprite = Cute.cf_make_demo_sprite
  assert_nil(Cute.cf_sprite_draw(sprite))
end

assert("Sprite") do
  sprite = Cute::Sprite.new(nil)
  assert_kind_of(Cute::Sprite, sprite)

  assert_equal(0, sprite.width)
  assert_equal(0, sprite.height)
end

assert("Sprite#playing?") do
  sprite = Cute::Sprite.new(Cute.cf_make_demo_sprite)
  assert_false(sprite.playing?("idle"))
  assert_false(sprite.playing?("walk"))
  sprite.play("idle")
  assert_true(sprite.playing?("idle"))
end
