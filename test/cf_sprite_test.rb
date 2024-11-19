assert("Cute::CF_Sprite#initialize") do
  cf_sprite = Cute::CF_Sprite.new
  assert_kind_of(Cute::CF_Sprite, cf_sprite)
end

assert("Cute::CF_Sprite#w") do
  cf_sprite = Cute::CF_Sprite.new
  assert_equal(0, cf_sprite.w)
end

assert("Cute::CF_Sprite#w=") do
  cf_sprite = Cute::CF_Sprite.new
  assert_equal(10, (cf_sprite.w = 10))
  assert_equal(10, cf_sprite.w)
end

assert("Cute::CF_Sprite#h") do
  cf_sprite = Cute::CF_Sprite.new
  assert_equal(0, cf_sprite.h)
end

assert("Cute::CF_Sprite#h=") do
  cf_sprite = Cute::CF_Sprite.new
  assert_equal(10, (cf_sprite.h = 10))
  assert_equal(10, cf_sprite.h)
end

assert("Cute::CF_Sprite#inspect") do
  cf_sprite = Cute::CF_Sprite.new
  cf_sprite.w = 6
  cf_sprite.h = 9
  assert_equal('#<Cute::CF_Sprite name:"" w:6 h:9 opacity:1.0>', cf_sprite.inspect)
end

assert("Cute::CF_Sprite#opacity") do
  cf_sprite = Cute::CF_Sprite.new
  assert_equal(1.0, cf_sprite.opacity)

  cf_sprite.opacity = 0.5
  assert_equal(0.5, cf_sprite.opacity)
end
