module Cute
  class Transform
    def inspect
      "#<Cute::Transform:#{sprintf("0x%x", (object_id << 1))} p:#{p.inspect} r:#{r.inspect}>"
    end
  end
end

