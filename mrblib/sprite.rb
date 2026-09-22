module Cute
  class Sprite
    # Factory class methods
    def self.demo
      Cute.cf_make_demo_sprite
    end

    def self.defaults
      Cute.cf_sprite_defaults
    end

    # Convenience methods
    def position
      transform.p
    end

    def position=(v2)
      transform.p = v2
    end

    def x
      transform.p.x
    end

    def x=(value)
      transform.p.x = value
    end

    def y
      transform.p.y
    end

    def y=(value)
      transform.p.y = value
    end

    def rotation
      transform.r
    end

    def rotation=(sincos)
      transform.r = sincos
    end

    # Chainable setters for fluent API
    def with_opacity(value)
      self.opacity = value
      self
    end

    def with_scale(x, y = nil)
      self.scale_x = x
      self.scale_y = y || x
      self
    end

    def with_position(x_or_v2, y = nil)
      if x_or_v2.is_a?(V2)
        self.position = x_or_v2
      else
        self.x = x_or_v2
        self.y = y
      end
      self
    end

    # Display methods
    def to_s
      "Sprite(#{name})"
    end

    def inspect
      "#<Cute::Sprite:#{sprintf("0x%x", (object_id << 1))} name:#{name.inspect} w:#{w} h:#{h} opacity:#{opacity}>"
    end
  end
end
