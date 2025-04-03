#!deps/mruby/bin/mruby

class Game
  include Cute
  def initialize
    puts "Hello, you are running #{cf_version_string_linked}!"

    result = cf_make_app("Example App", 0, 0, 0, 800, 600, CF_APP_OPTIONS_WINDOW_POS_CENTERED_BIT, "example.rb")

    if cf_is_error(result)
      puts "Error creating app: #{result.details}"
      exit(1)
    end

    cf_app_set_vsync(true)
    cf_set_target_framerate(60)
    cf_set_fixed_timestep(60)
    cf_set_fixed_timestep_max_updates(1)
    @sprites = Array.new(5000) do
      cf_make_demo_sprite.tap do |s|
        s.transform.p.x = rand(800) - 400
        s.transform.p.y = rand(600) - 300
        s.play("spin")
      end
    end

    @sprite = cf_make_demo_sprite
    @sprite.play("spin")
    @sprite.transform.p.x = 0
    @sprite.transform.p.y = 0
  end

  def run
    while cf_app_is_running
      cf_app_update(&method(:update))
      cf_app_draw_onto_screen(true)
    end

    cf_app_destroy
  end

  def update
    cf_app_set_title("Example App - FPS:#{"%.2f" % cf_app_get_smoothed_framerate} DPI:#{cf_app_get_dpi_scale} - #{cf_app_get_width}x#{cf_app_get_height} Sprites:#{@sprites.size}")

    if cf_app_get_smoothed_framerate > 58
      10.times do
        cf_make_demo_sprite.tap do |s|
          s.play("spin")
          s.transform.p.x = rand(800) - 400
          s.transform.p.y = rand(600) - 300
          @sprites << s
        end
      end
    end

    if cf_key_just_pressed(CF_KEY_W)
      puts "Key W pressed"
      @sprite.transform.p.y += 8
    end

    if cf_key_just_pressed(CF_KEY_S)
      puts "Key S pressed"
      @sprite.transform.p.y -= 8
    end

    if cf_key_just_pressed(CF_KEY_A)
      puts "Key A pressed"
      @sprite.transform.p.x -= 8
    end

    if cf_key_just_pressed(CF_KEY_D)
      puts "Key D pressed"
      @sprite.transform.p.x += 8
    end

    @sprite.update

    i = 0
    scount = @sprites.size
    while i < scount
      s = @sprites[i]
      p = s.transform.p
      p.x -= 1
      p.y -= 1
      if p.x < -400
        p.x = 400
      end

      if p.y < -300
        p.y = 300
      end
      s.update
      s.draw
      i += 1
    end

    cf_draw_push
    cf_draw_scale(4.0, 4.0)
    @sprite.draw
    cf_draw_text("Hello, world!", @sprite.transform.p)
    cf_draw_pop
  end
end

if __FILE__ == $0
  Game.new.run
end
