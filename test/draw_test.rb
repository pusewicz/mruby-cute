def within_app(&block)
  Cute.cf_make_app("Test App", 0, 10, 10, 800, 600, 0, "test_app")
  Cute.cf_app_update
  block.call
  Cute.cf_app_update
  Cute.cf_app_destroy
end

assert('Cute::cf_draw_line') do
  within_app do
    # Create two vectors
    v1 = Cute::V2.new(10, 10)
    v2 = Cute::V2.new(100, 100)

    # This should not raise an error
    assert_nothing_raised do
      Cute::cf_draw_line(v1, v2, 2.0)
    end
  end
end
