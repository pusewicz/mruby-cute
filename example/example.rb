#!deps/mruby/bin/mruby

include Cute

puts "Hello, you are running #{cf_version_string_linked}!"

result = cf_make_app("Example App", 0, 0, 0, 800, 600, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

if cf_is_error(result)
  puts "Error creating app: #{result.details}"
  exit(1)
end

sprite = cf_make_demo_sprite
sprite.play("spin")

def puts_sprite(sprite)
  puts sprite.inspect
  puts "Sprite position: #{sprite.transform.p.x}, #{sprite.transform.p.y}"
  puts "Transform: #{sprite.transform.inspect}"
  puts "Position: #{sprite.transform.p.inspect}"
end

while cf_app_is_running
  cf_app_update

  cf_draw_text("Hello, world!", sprite.transform.p)

  if cf_key_just_pressed(CF_KEY_W)
    puts "Key W pressed"
    sprite.transform.p.y += 8
    puts_sprite(sprite)
  end

  if cf_key_just_pressed(CF_KEY_S)
    puts "Key S pressed"
    sprite.transform.p.y -= 8
    puts_sprite(sprite)
  end

  if cf_key_just_pressed(CF_KEY_A)
    puts "Key A pressed"
    sprite.transform.p.x -= 8
    puts_sprite(sprite)
  end

  if cf_key_just_pressed(CF_KEY_D)
    puts "Key D pressed"
    sprite.transform.p.x += 8
    puts_sprite(sprite)
  end

  if cf_key_just_pressed(CF_KEY_SPACE)
    puts_sprite(sprite)
  end

  sprite.update
  sprite.draw

  cf_app_draw_onto_screen
end

cf_app_destroy
