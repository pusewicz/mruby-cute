module Cute
  class V2
    def ==(other)
      return false unless other.is_a?(V2)

      x == other.x && y == other.y
    end

    def to_s
      "V2(#{x}, #{y})"
    end

    def inspect
      "#<Cute::V2:0x#{object_id.to_s(16)} x=#{x} y=#{y}>"
    end

    def to_a
      [x, y]
    end

    def to_h
      {x: x, y: y}
    end

    def hash
      [x, y].hash
    end

    def eql?(other)
      self == other
    end
  end
end
