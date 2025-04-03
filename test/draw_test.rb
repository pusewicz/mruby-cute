def within_app(&block)
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  Cute.cf_app_update
  block.call
  Cute.cf_app_update
  Cute.cf_app_destroy
end

assert("Cute::cf_draw_line") do
  within_app do
    # Create two vectors
    v1 = Cute::V2.new(10, 10)
    v2 = Cute::V2.new(100, 100)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_line(v1, v2, 2.0)
    end
  end
end

assert("Cute::cf_draw_quad") do
  within_app do
    # Create min and max points for AABB
    min = Cute::V2.new(10, 10)
    max = Cute::V2.new(100, 100)

    # Create an AABB
    bb = Cute::Aabb.new(min, max)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_quad(bb, 2.0, 0.0)
    end
  end
end

assert("Cute::cf_draw_quad2") do
  within_app do
    # Create four points for quad
    p0 = Cute::V2.new(10, 10)
    p1 = Cute::V2.new(100, 10)
    p2 = Cute::V2.new(100, 100)
    p3 = Cute::V2.new(10, 100)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_quad2(p0, p1, p2, p3, 2.0, 0.0)
    end
  end
end

assert("Cute::cf_draw_rotate") do
  within_app do
    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_rotate(Math::PI / 4.0)  # 45 degrees in radians
    end
  end
end

assert("Cute::cf_draw_translate") do
  within_app do
    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_translate(50.0, 75.0)
    end
  end
end

assert("Cute::cf_draw_translate_v2") do
  within_app do
    # Create a vector for translation
    position = Cute::V2.new(50.0, 75.0)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_translate_v2(position)
    end
  end
end

assert("Cute::cf_draw_circle") do
  within_app do
    # Create a position for the circle
    position = Cute::V2.new(100.0, 100.0)

    # Create a circle with radius 50
    circle = Cute::Circle.new(position, 50.0)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_circle(circle, 2.0)
    end
  end
end

assert("Cute::cf_draw_circle2") do
  within_app do
    # Create a position for the circle
    position = Cute::V2.new(100.0, 100.0)

    # This should not raise an error
    assert_nothing_raised do
      Cute.cf_draw_circle2(position, 50.0, 2.0)
    end
  end
end

assert("Cute::cf_make_font") do
  within_app do
    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_make_font("font.ttf", "test_font")
    end
  end
end

assert("Cute::cf_push_font and cf_pop_font") do
  within_app do
    # Just test that the functions exist and don't crash
    assert_nothing_raised do
      Cute.cf_push_font("default")
      Cute.cf_pop_font
    end
  end
end

assert("Cute::cf_push_font_size and cf_pop_font_size") do
  within_app do
    # Just test that the functions exist and don't crash
    assert_nothing_raised do
      Cute.cf_push_font_size(16.0)
      Cute.cf_pop_font_size
    end
  end
end

assert("Cute::cf_draw_text") do
  within_app do
    # Create a position for the text
    position = Cute::V2.new(100.0, 100.0)

    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_draw_text("Hello, world!", position)
    end
  end
end

assert("Cute::cf_draw_text with num_chars") do
  within_app do
    # Create a position for the text
    position = Cute::V2.new(100.0, 100.0)

    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_draw_text("Hello, world!", position, 5)  # Draw only "Hello"
    end
  end
end

assert("Cute::cf_text_width") do
  within_app do
    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_text_width("Hello, world!")
    end
  end
end

assert("Cute::cf_text_height") do
  within_app do
    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_text_height("Hello, world!")
    end
  end
end

assert("Cute::cf_text_size") do
  within_app do
    # Just test that the function exists and doesn't crash
    assert_nothing_raised do
      Cute.cf_text_size("Hello, world!")
    end
  end
end
