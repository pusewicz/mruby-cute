assert('Cute::cf_draw_line') do
  # Create two vectors
  v1 = Cute::V2.new(10, 10)
  v2 = Cute::V2.new(100, 100)
  
  # This should not raise an error
  assert_nothing_raised do
    Cute::cf_draw_line(v1, v2, 2.0)
  end
end
