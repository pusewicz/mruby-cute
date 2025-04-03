def within_app(&block)
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  Cute.cf_app_update
  block.call
  Cute.cf_app_update
  Cute.cf_app_destroy
end

assert('Cute::cf_draw_line') do
  within_app do
    # Create two vectors
    v1 = Cute::V2.new(10, 10)
    v2 = Cute::V2.new(100, 100)
    
    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_line(v1, v2, 2.0)
    end
  end
end

assert('Cute::cf_draw_quad') do
  within_app do
    # Create min and max points for AABB
    min = Cute::V2.new(10, 10)
    max = Cute::V2.new(100, 100)
    
    # Create an AABB
    bb = Cute::Aabb.new(min, max)
    
    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_quad(bb, 2.0, 0.0)
    end
  end
end

assert('Cute::cf_draw_quad2') do
  within_app do
    # Create four points for quad
    p0 = Cute::V2.new(10, 10)
    p1 = Cute::V2.new(100, 10)
    p2 = Cute::V2.new(100, 100)
    p3 = Cute::V2.new(10, 100)
    
    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_quad2(p0, p1, p2, p3, 2.0, 0.0)
    end
  end
end

assert('Cute::cf_draw_quad') do
  within_app do
    # Create min and max points for AABB
    min = Cute::V2.new(10, 10)
    max = Cute::V2.new(100, 100)

    # Create an AABB
    bb = Cute::Aabb.new(min, max)

    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_quad(bb, 2.0, 0.0)
    end
  end
end

assert('Cute::cf_draw_quad2') do
  within_app do
    # Create four points for quad
    p0 = Cute::V2.new(10, 10)
    p1 = Cute::V2.new(100, 10)
    p2 = Cute::V2.new(100, 100)
    p3 = Cute::V2.new(10, 100)

    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_quad2(p0, p1, p2, p3, 2.0, 0.0)
    end
  end
end

assert('Cute::cf_draw_rotate') do
  within_app do
    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_rotate(Math::PI / 4.0)  # 45 degrees in radians
    end
  end
end
