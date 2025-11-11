module Cute
  module_function

  # Unified circle drawing - accepts Circle object or position + radius
  def draw_circle(circle_or_position, radius_or_thickness = nil, thickness = 0)
    case circle_or_position
    when Circle
      cf_draw_circle(circle_or_position, radius_or_thickness || 0)
    when V2
      cf_draw_circle2(circle_or_position, radius_or_thickness, thickness)
    else
      raise TypeError, "expected Circle or V2, got #{circle_or_position.class}"
    end
  end

  # Unified circle fill - accepts Circle object or position + radius
  def draw_circle_fill(circle_or_position, radius = nil)
    case circle_or_position
    when Circle
      cf_draw_circle_fill(circle_or_position)
    when V2
      cf_draw_circle_fill2(circle_or_position, radius)
    else
      raise TypeError, "expected Circle or V2, got #{circle_or_position.class}"
    end
  end

  # Unified quad drawing - accepts Aabb or 4 V2 points
  def draw_quad(bb_or_p0, thickness_or_p1 = nil, chubbiness_or_p2 = nil, p3 = nil, thickness = 0, chubbiness = 0)
    case bb_or_p0
    when Aabb
      cf_draw_quad(bb_or_p0, thickness_or_p1, chubbiness_or_p2)
    when V2
      cf_draw_quad2(bb_or_p0, thickness_or_p1, chubbiness_or_p2, p3, thickness, chubbiness)
    else
      raise TypeError, "expected Aabb or V2, got #{bb_or_p0.class}"
    end
  end

  # Block-based transform API for cleaner code
  def with_transform(scale: nil, rotate: nil, translate: nil)
    cf_draw_push
    begin
      if scale
        scale.is_a?(Array) ? cf_draw_scale(*scale) : cf_draw_scale(scale, scale)
      end
      cf_draw_rotate(rotate) if rotate
      if translate
        translate.is_a?(V2) ? cf_draw_translate_v2(translate) : cf_draw_translate(*translate)
      end
      yield
    ensure
      cf_draw_pop
    end
  end

  # Alias for clarity
  def draw_sprite(sprite)
    cf_draw_sprite(sprite)
  end

  def draw_line(p0, p1, thickness)
    cf_draw_line(p0, p1, thickness)
  end

  def draw_text(text, position, num_chars = -1)
    cf_draw_text(text, position, num_chars)
  end

  # Transform stack operations (for manual control)
  def push_transform
    cf_draw_push
  end

  def pop_transform
    cf_draw_pop
  end

  def scale(x, y = nil)
    y ||= x
    cf_draw_scale(x, y)
  end

  def translate(x_or_v2, y = nil)
    if x_or_v2.is_a?(V2)
      cf_draw_translate_v2(x_or_v2)
    else
      cf_draw_translate(x_or_v2, y)
    end
  end

  def rotate(radians)
    cf_draw_rotate(radians)
  end
end
