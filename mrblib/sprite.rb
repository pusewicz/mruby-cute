module Cute
  class Sprite
    def to_s
      "Sprite(#{name})"
    end

    def inspect
      "#<Cute::Sprite:#{sprintf("0x%x", (object_id << 1))} name:#{name.inspect} w:#{w} h:#{h} opacity:#{opacity}>"
    end
  end
end
