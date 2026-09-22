module Cute
  class Aabb
    def to_s
      "Aabb(min=#{min.to_s}, max=#{max.to_s})"
    end

    def inspect
      "#<Cute::Aabb:0x#{object_id.to_s(16)} min=#{min.inspect} max=#{max.inspect}>"
    end
  end
end
