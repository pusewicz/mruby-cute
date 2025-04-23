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

    @sprites = []

    @sprite = cf_make_demo_sprite
    @sprite.play("spin")
    @sprite.transform.p.x = 0
    @sprite.transform.p.y = 0

    puts "GC.interval_ratio: #{GC.interval_ratio}"
    puts "GC.step_ratio: #{GC.step_ratio}"
    puts "GC.generational_mode: #{GC.generational_mode}"
  end

  def run
    while cf_app_is_running
      cf_app_update(&method(:update))
      cf_app_draw_onto_screen(true)
      GC.start
    end

    cf_app_destroy
  end

  def update
    h = {}
    cf_app_set_title("Example App - FPS:#{"%.2f" % cf_app_get_smoothed_framerate} DPI:#{cf_app_get_dpi_scale} - #{cf_app_get_width}x#{cf_app_get_height} Sprites:#{@sprites.size}")

    if cf_key_just_pressed(CF_KEY_SPACE)
      ObjectSpace.count_objects(h)
      puts "# ObjectSpace"
      puts h
      puts "#" * 80
      puts "# Ticks"
      puts "cf_get_ticks: #{cf_get_ticks}"
      puts "CF_TICKS: #{CF_TICKS()}"
      puts "CF_DELTA_TIME: #{CF_DELTA_TIME()}"
      puts "CF_DELTA_TIME_FIXED: #{CF_DELTA_TIME_FIXED()}"
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

    cf_draw_push
    cf_draw_scale(4.0, 4.0)
    cf_draw_circle_fill2(V2(0, 0), 32)
    @sprite.draw
    cf_draw_pop
  end
end

if __FILE__ == $0
  Game.new.run
end
