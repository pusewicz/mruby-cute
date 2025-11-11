module Cute
  class Color
    # Factory class methods - idiomatic Ruby API
    def self.rgb(r, g, b)
      new(r / 255.0, g / 255.0, b / 255.0, 1.0)
    end

    def self.rgba(r, g, b, a)
      new(r / 255.0, g / 255.0, b / 255.0, a / 255.0)
    end

    def self.rgb_f(r, g, b)
      new(r, g, b, 1.0)
    end

    def self.rgba_f(r, g, b, a)
      new(r, g, b, a)
    end

    def self.hex(value)
      Cute.cf_make_color_hex(value)
    end

    # Predefined colors as class methods
    def self.clear;   rgb_f(0.0, 0.0, 0.0, 0.0); end
    def self.black;   rgb_f(0.0, 0.0, 0.0, 1.0); end
    def self.white;   rgb_f(1.0, 1.0, 1.0, 1.0); end
    def self.red;     rgb_f(1.0, 0.0, 0.0, 1.0); end
    def self.green;   rgb_f(0.0, 1.0, 0.0, 1.0); end
    def self.blue;    rgb_f(0.0, 0.0, 1.0, 1.0); end
    def self.yellow;  rgb_f(1.0, 1.0, 0.0, 1.0); end
    def self.cyan;    rgb_f(0.0, 1.0, 1.0, 1.0); end
    def self.magenta; rgb_f(1.0, 0.0, 1.0, 1.0); end
    def self.grey;    rgb_f(0.5, 0.5, 0.5, 1.0); end
    def self.orange;  rgb_f(1.0, 0.5, 0.0, 1.0); end
    def self.purple;  rgb_f(0.5, 0.0, 0.5, 1.0); end
    def self.brown;   rgb_f(0.6, 0.4, 0.2, 1.0); end

    # Instance methods
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
    # Factory class methods
    def self.rgb(r, g, b)
      new(r, g, b, 255)
    end

    def self.rgba(r, g, b, a)
      new(r, g, b, a)
    end

    def self.hex(value)
      Cute.cf_pixel_hex(value)
    end

    # Instance methods
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
