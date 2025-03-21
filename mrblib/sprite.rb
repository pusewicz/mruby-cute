module Cute
  class Sprite
    def inspect
      "#<Cute::Sprite:#{sprintf("0x%x", (object_id << 1))} name:#{name.inspect} w:#{w} h:#{h} opacity:#{opacity}>"
    end
  end
end
