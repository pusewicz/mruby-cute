module Cute
  class Sprite
    def initialize(cf_sprite)
      @cf_sprite = cf_sprite || Cute.cf_sprite_defaults
    end

    def width = Cute.cf_sprite_width(@cf_sprite)
    def height = Cute.cf_sprite_height(@cf_sprite)
    def playing?(name) = Cute.cf_sprite_is_playing(@cf_sprite, name)
    def play(name) = Cute.cf_sprite_play(@cf_sprite, name)
    def pause = Cute.cf_sprite_pause(@cf_sprite)
    def unpause = Cute.cf_sprite_unpause(@cf_sprite)
    def update = Cute.cf_sprite_update(@cf_sprite)
    def draw = Cute.cf_sprite_draw(@cf_sprite)
  end
end
