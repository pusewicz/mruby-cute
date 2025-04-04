module Cute
  class V2
    def ==(other)
      return false unless other.is_a?(V2)

      x == other.x && y == other.y
    end
  end
end
