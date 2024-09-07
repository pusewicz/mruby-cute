assert("cf_sprite_width") do
  sprite = Cute.cf_sprite_defaults
  assert_equal(0, Cute.cf_sprite_width(sprite))
end

assert("cf_sprite_height") do
  sprite = Cute.cf_sprite_defaults
  assert_equal(0, Cute.cf_sprite_height(sprite))
end

assert("Sprite") do
  sprite = Cute::Sprite.new(nil)
  assert_kind_of(Cute::Sprite, sprite)

  assert_equal(0, sprite.width)
  assert_equal(0, sprite.height)
end
