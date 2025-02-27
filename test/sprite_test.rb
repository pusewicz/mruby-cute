def within_app(&block)
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  Cute.cf_app_update
  block.call
  Cute.cf_app_update
  Cute.cf_app_destroy
end

assert("Cute::Sprite#initialize") do
  sprite = Cute::Sprite.new
  assert_kind_of(Cute::Sprite, sprite)
end

assert("Cute::Sprite#w") do
  sprite = Cute::Sprite.new
  assert_equal(0, sprite.w)
end

assert("Cute::Sprite#w=") do
  sprite = Cute::Sprite.new
  assert_equal(10, (sprite.w = 10))
  assert_equal(10, sprite.w)
end

assert("Cute::Sprite#h") do
  sprite = Cute::Sprite.new
  assert_equal(0, sprite.h)
end

assert("Cute::Sprite#h=") do
  sprite = Cute::Sprite.new
  assert_equal(10, (sprite.h = 10))
  assert_equal(10, sprite.h)
end

assert("Cute::Sprite#opacity") do
  sprite = Cute::Sprite.new
  sprite.opacity = 0.5
  assert_equal(0.5, sprite.opacity)
end

assert("Cute::Sprite#scale_x") do
  sprite = Cute::Sprite.new
  sprite.scale_x = 1.5
  assert_equal(1.5, sprite.scale_x)
end

assert("Cute::Sprite#scale_y") do
  sprite = Cute::Sprite.new
  sprite.scale_y = 1.5
  assert_equal(1.5, sprite.scale_y)
end

assert("Cute::Sprite#reset") do
  within_app do
    sprite = Cute.cf_make_demo_sprite
    assert_nil(sprite.reset)
  end
end

assert("Cute::Sprite#inspect") do
  sprite = Cute::Sprite.new
  sprite.w = 6
  sprite.h = 9
  assert_equal('#<Cute::Sprite name:"" w:6 h:9 opacity:1.0>', sprite.inspect)
end

assert("Cute::Sprite#draw") do
  within_app do
    sprite = Cute.cf_make_demo_sprite
    sprite.play("spin")
    sprite.update
    assert_nil(sprite.draw)
  end
end

assert("Cute::Sprite#loop") do
  sprite = Cute::Sprite.new
  assert_true(sprite.loop)
  sprite.loop = false
  assert_false(sprite.loop)
  sprite.loop = true
  assert_true(sprite.loop)
end
