module Cute
  class Sprite
    # @return [Float] the width of the sprite
    attr_accessor :w

    # @return [Float] the height of the sprite
    attr_accessor :h

    # Draws the sprite on the screen
    # @return nil
    def draw
    end

    # Updates the sprite's animation
    # @return nil
    def update
    end

    # Switches to a new animation and starts playing it from the beginning
    # @param name [String] the name of the animation to play
    # @return nil
    def play(name)
    end

    # Returns true if the sprite is currently playing the animation
    # @param name [String] the name of the animation
    # @return [Boolean]
    def playing?(name)
    end

    # Returns whether animations will loop
    # @return [Boolean] true if animations loop, false if they stop at the last frame
    def loop
    end

    # Sets whether animations will loop
    # @param value [Boolean] true to make animations loop, false to make them stop at the last frame
    # @return [Boolean] the new loop value
    def loop=(value)
    end
  end
end
