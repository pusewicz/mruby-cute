module Cute
  class Circle
    def to_s
      "Circle(x=#{x}, y=#{y}, r=#{r})"
    end

    def inspect
      "#<Cute::Circle:0x#{object_id.to_s(16)} x=#{x} y=#{y} r=#{r}>"
    end
  end
end
