#!../mruby/build/host/bin/mruby

include Cute

puts "Hello, you are running #{version_string_linked}!"

result = make_app("Example App", 0, 0, 0, 800, 600, APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

if result.error?
  puts "Error creating app: #{result.details}"
  exit(1)
end

sprite = Sprite.make_demo_sprite
sprite.play("spin")

while app_is_running
  app_update
  sprite.update
  sprite.draw
  app_draw_onto_screen
end

app_destroy
