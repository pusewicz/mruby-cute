module Cute
  class Color
    def ==(other)
      return false unless other.is_a?(Color)

      r == other.r && g == other.g && b == other.b && a == other.a
    end

    def to_s
      "Color(r=#{r}, g=#{g}, b=#{b}, a=#{a})"
    end

    def inspect
      "#<Cute::Color:0x#{object_id.to_s(16)} r=#{r} g=#{g} b=#{b} a=#{a}>"
    end

    def to_a
      [r, g, b, a]
    end

    def to_h
      {r: r, g: g, b: b, a: a}
    end

    # Hash for use in Hash keys
    def hash
      [r, g, b, a].hash
    end

    def eql?(other)
      self == other
    end
  end

  class Pixel
    def ==(other)
      return false unless other.is_a?(Pixel)

      r == other.r && g == other.g && b == other.b && a == other.a
    end

    def to_s
      "Pixel(#{r}, #{g}, #{b}, #{a})"
    end

    def inspect
      "#<Cute::Pixel:0x#{object_id.to_s(16)} r=#{r} g=#{g} b=#{b} a=#{a}>"
    end

    def to_a
      [r, g, b, a]
    end

    def to_h
      {r: r, g: g, b: b, a: a}
    end

    def hash
      [r, g, b, a].hash
    end

    def eql?(other)
      self == other
    end
  end
end
