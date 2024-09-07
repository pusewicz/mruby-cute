#!../mruby/build/host/bin/mruby

include Cute

puts "Hello, you are running #{cf_version_string_linked}!"

result = cf_make_app("Example App", 0, 0, 0, 800, 600, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

if cf_is_error(result)
  puts "Error creating app: #{result.details}"
  exit(1)
end

sprite = Sprite.new(cf_make_demo_sprite)
sprite.play("spin")

while cf_app_is_running
  cf_app_update
  sprite.update
  sprite.draw
  cf_app_draw_onto_screen
end

cf_app_destroy
