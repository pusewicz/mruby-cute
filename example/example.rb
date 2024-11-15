#!deps/mruby/bin/mruby

include Cute

puts "Hello, you are running #{cf_version_string_linked}!"

result = cf_make_app("Example App", 0, 0, 0, 800, 600, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

if cf_is_error(result)
  puts "Error creating app: #{result.details}"
  exit(1)
end

sprite = cf_make_demo_sprite
cf_sprite_play(sprite, "spin")

while cf_app_is_running
  cf_app_update
  cf_sprite_update(sprite)
  cf_sprite_draw(sprite)
  cf_app_draw_onto_screen

  puts "W key pressed" if cf_key_just_pressed(CF_KEY_W)
  puts "S key pressed" if cf_key_just_pressed(CF_KEY_S)
  puts "A key pressed" if cf_key_just_pressed(CF_KEY_A)
  puts "D key pressed" if cf_key_just_pressed(CF_KEY_D)
end

cf_app_destroy
