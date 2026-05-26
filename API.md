# mruby-cute API Guide

This document shows the modern, idiomatic Ruby API for mruby-cute.

## Color API

### Old (C-style) vs New (Ruby-idiomatic)

```ruby
# ❌ Old - C-style factories
color = Cute.cf_make_color_rgb(255, 128, 0)
color = Cute.cf_make_color_rgba_f(1.0, 0.5, 0.0, 1.0)
color = Cute.cf_color_red

# ✅ New - Ruby class methods
color = Cute::Color.rgb(255, 128, 0)
color = Cute::Color.rgba_f(1.0, 0.5, 0.0, 1.0)
color = Cute::Color.red

# Predefined colors
Cute::Color.red
Cute::Color.green
Cute::Color.blue
Cute::Color.white
Cute::Color.black
Cute::Color.yellow
Cute::Color.cyan
Cute::Color.magenta
Cute::Color.grey
Cute::Color.orange
Cute::Color.purple
Cute::Color.brown
Cute::Color.clear

# Hex colors
color = Cute::Color.hex(0xFF8000)
```

## Vector API

### Creating Vectors

```ruby
# Old module function (still works)
v = Cute.V2(10, 20)

# ✅ Better - use class constructor
v = Cute::V2.new(10, 20)
```

### Math Operations

```ruby
v1 = Cute::V2.new(10, 20)
v2 = Cute::V2.new(5, 3)

# Vector operations
v3 = v1 + v2      # V2(15, 23)
v4 = v1 - v2      # V2(5, 17)
v5 = v1 * 2.0     # V2(20, 40)
v6 = v1 / 2.0     # V2(5, 10)
v7 = -v1          # V2(-10, -20)

# Conversions
v1.to_a           # [10, 20]
v1.to_h           # {x: 10, y: 20}
v1.to_s           # "V2(10, 20)"
```

## Sprite API

### Old vs New

```ruby
# ❌ Old - C-style factory
sprite = Cute.cf_make_demo_sprite

# ✅ New - Ruby class method
sprite = Cute::Sprite.demo

# Position access - Old
sprite.transform.p.x = 100
sprite.transform.p.y = 200

# ✅ Position access - New (convenience)
sprite.x = 100
sprite.y = 200
sprite.position = Cute::V2.new(100, 200)

# ✅ Fluent API
sprite = Cute::Sprite.demo
  .with_position(100, 200)
  .with_scale(2.0)
  .with_opacity(0.8)
```

## Drawing API

### Unified Draw Methods

```ruby
# ❌ Old - Numbered variants
Cute.cf_draw_circle(circle, thickness)
Cute.cf_draw_circle2(position, radius, thickness)
Cute.cf_draw_circle_fill(circle)
Cute.cf_draw_circle_fill2(position, radius)

# ✅ New - Unified methods (polymorphic)
circle = Cute::Circle.new(position, radius)
Cute.draw_circle(circle, thickness)
Cute.draw_circle(position, radius, thickness)  # Same method!

Cute.draw_circle_fill(circle)
Cute.draw_circle_fill(position, radius)  # Same method!
```

### Block-based Transforms

```ruby
# ❌ Old - Manual push/pop
Cute.cf_draw_push
Cute.cf_draw_scale(2.0, 2.0)
Cute.cf_draw_rotate(Math::PI / 4)
Cute.cf_draw_translate(100, 200)
sprite.draw
Cute.cf_draw_pop

# ✅ New - Block-based (automatic cleanup)
Cute.with_transform(scale: 2.0, rotate: Math::PI / 4, translate: [100, 200]) do
  sprite.draw
end

# Or individual methods
Cute.scale(2.0)
Cute.translate(100, 200)
Cute.rotate(Math::PI / 4)
```

## Complete Example

```ruby
include Cute

# Create entities
player = Sprite.demo
  .with_position(100, 100)
  .with_scale(2.0)
  .with_opacity(0.9)

enemy_pos = V2.new(200, 150)
player_color = Color.red
background = Color.rgb(20, 20, 30)

# Game loop
def update
  # Update player position with math operators
  velocity = V2.new(1, 0)
  player.position = player.position + velocity

  # Draw with unified API
  with_transform(scale: 2.0) do
    draw_circle_fill(enemy_pos, 32)
    player.draw
  end
end
```

## Migration Tips

1. **Colors**: Replace `cf_make_color_*` with `Color.rgb` / `Color.rgba_f`
2. **Predefined colors**: Replace `cf_color_red` with `Color.red`
3. **Sprites**: Replace `cf_make_demo_sprite` with `Sprite.demo`
4. **Drawing**: Use unified `draw_circle` instead of `cf_draw_circle2`
5. **Transforms**: Use `with_transform` blocks instead of manual push/pop
6. **Vectors**: Use `V2.new` instead of `V2()` module function

## Compatibility

All old C-style functions still work! The new API is a Ruby layer on top.
You can migrate incrementally without breaking existing code.
