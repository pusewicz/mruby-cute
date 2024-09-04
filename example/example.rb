#!../mruby/build/host/bin/mruby

puts "Hello, you are running #{Cute.version_string_linked}!"

result = Cute.make_app("Example App", 0, 0, 0, 800, 600, Cute::APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

if result.error?
  puts "Error creating app: #{result.details}"
  exit(1)
end

sprite = Cute::Sprite.make_demo_sprite
sprite.play("spin")

while Cute.app_is_running
  Cute.app_update
  sprite.update
  sprite.draw
  Cute.app_draw_onto_screen
end

Cute.destroy_app
