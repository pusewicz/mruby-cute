def assert_float_delta(expected, actual, delta = 1e-5)
  assert_true((expected - actual).abs <= delta, "Expected #{expected} to be within #{delta} of #{actual}")
end

assert("Cute::Color#new") do
  color = Cute::Color.new
  assert_float_delta(0.0, color.r)
  assert_float_delta(0.0, color.g)
  assert_float_delta(0.0, color.b)
  assert_float_delta(1.0, color.a)

  color = Cute::Color.new(0.5, 0.6, 0.7, 0.8)
  assert_float_delta(0.5, color.r)
  assert_float_delta(0.6, color.g)
  assert_float_delta(0.7, color.b)
  assert_float_delta(0.8, color.a)
end

assert("Cute::Color setters") do
  color = Cute::Color.new
  color.r = 0.1
  color.g = 0.2
  color.b = 0.3
  color.a = 0.4
  assert_float_delta(0.1, color.r)
  assert_float_delta(0.2, color.g)
  assert_float_delta(0.3, color.b)
  assert_float_delta(0.4, color.a)
end

assert("Cute::Color factory methods") do
  color = Cute.cf_make_color_rgb_f(0.1, 0.2, 0.3)
  assert_float_delta(0.1, color.r)
  assert_float_delta(0.2, color.g)
  assert_float_delta(0.3, color.b)
  assert_float_delta(1.0, color.a)

  color = Cute.cf_make_color_rgba_f(0.1, 0.2, 0.3, 0.4)
  assert_float_delta(0.1, color.r)
  assert_float_delta(0.2, color.g)
  assert_float_delta(0.3, color.b)
  assert_float_delta(0.4, color.a)

  color = Cute.cf_make_color_rgb(128, 192, 255)
  assert_float_delta(128.0 / 255.0, color.r)
  assert_float_delta(192.0 / 255.0, color.g)
  assert_float_delta(1.0, color.b)
  assert_float_delta(1.0, color.a)

  color = Cute.cf_make_color_rgba(128, 192, 255, 64)
  assert_float_delta(128.0 / 255.0, color.r)
  assert_float_delta(192.0 / 255.0, color.g)
  assert_float_delta(1.0, color.b)
  assert_float_delta(64.0 / 255.0, color.a)
end

assert("Cute::Color presets") do
  color = Cute.cf_color_red
  assert_float_delta(1.0, color.r)
  assert_float_delta(0.0, color.g)
  assert_float_delta(0.0, color.b)
  assert_float_delta(1.0, color.a)

  color = Cute.cf_color_green
  assert_float_delta(0.0, color.r)
  assert_float_delta(1.0, color.g)
  assert_float_delta(0.0, color.b)
  assert_float_delta(1.0, color.a)

  color = Cute.cf_color_blue
  assert_float_delta(0.0, color.r)
  assert_float_delta(0.0, color.g)
  assert_float_delta(1.0, color.b)
  assert_float_delta(1.0, color.a)
end

assert("Cute::Pixel#new") do
  pixel = Cute::Pixel.new
  assert_equal(0, pixel.r)
  assert_equal(0, pixel.g)
  assert_equal(0, pixel.b)
  assert_equal(255, pixel.a)

  pixel = Cute::Pixel.new(128, 192, 255, 64)
  assert_equal(128, pixel.r)
  assert_equal(192, pixel.g)
  assert_equal(255, pixel.b)
  assert_equal(64, pixel.a)
end

assert("Cute::Pixel setters") do
  pixel = Cute::Pixel.new
  pixel.r = 10
  pixel.g = 20
  pixel.b = 30
  pixel.a = 40
  assert_equal(10, pixel.r)
  assert_equal(20, pixel.g)
  assert_equal(30, pixel.b)
  assert_equal(40, pixel.a)
end

assert("Cute::Pixel factory methods") do
  pixel = Cute.cf_pixel_rgb(10, 20, 30)
  assert_equal(10, pixel.r)
  assert_equal(20, pixel.g)
  assert_equal(30, pixel.b)
  assert_equal(255, pixel.a)

  pixel = Cute.cf_pixel_rgba(10, 20, 30, 40)
  assert_equal(10, pixel.r)
  assert_equal(20, pixel.g)
  assert_equal(30, pixel.b)
  assert_equal(40, pixel.a)
end
