# assert("Cute::Sprite.make_sprite") do
#   sprite = Cute::Sprite.make_sprite("test_sprite.ase")
#   assert_kind_of(Cute::Sprite, sprite)
# end

assert("Cute::Sprite.make_demo_sprite") do
  Cute.make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  demo_sprite = Cute::Sprite.make_demo_sprite
  assert_kind_of(Cute::Sprite, demo_sprite)
end
