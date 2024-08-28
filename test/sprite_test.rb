# assert("Cute::Sprite.make_sprite") do
#   sprite = Cute::Sprite.make_sprite("test_sprite.ase")
#   assert_kind_of(Cute::Sprite, sprite)
# end

assert("Cute::Sprite.cf_make_demo_sprite") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  demo_sprite = Cute.cf_make_demo_sprite
  assert_kind_of(Cute::CF_Sprite, demo_sprite)
  Cute.cf_app_destroy
end

assert("Cute::Sprite#draw") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  sprite = Cute::Sprite.new
  assert_nothing_raised { sprite.draw }
  Cute.cf_app_destroy
end

assert("Cute::Sprite#play") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  sprite = Cute::Sprite.new
  assert_nothing_raised { sprite.play("idle") }
  Cute.cf_app_destroy
end

assert("Cute::Sprite#update") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  sprite = Cute::Sprite.new
  sprite.play("idle")
  assert_nothing_raised { sprite.update }
  Cute.cf_app_destroy
end

assert("Cute::Sprite#playing?") do
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  sprite = Cute::Sprite.new
  sprite.play("idle")
  assert_true(sprite.playing?("idle"))
  assert_false(sprite.playing?("walk"))
  sprite.play("spin")
  assert_false(sprite.playing?("idle"))
  assert_true(sprite.playing?("spin"))
  Cute.cf_app_destroy
end
