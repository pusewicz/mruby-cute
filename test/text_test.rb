assert 'Cute::cf_make_font' do
  result = Cute::cf_make_font('non_existent_file.ttf', 'test_font')
  assert_true Cute::cf_is_error(result)
end

assert 'Cute::cf_push_font and Cute::cf_pop_font' do
  # Just test that the methods exist and can be called without errors
  Cute::cf_push_font('default')
  Cute::cf_pop_font
  assert_true true
end

assert 'Cute::cf_push_font_size and Cute::cf_pop_font_size' do
  # Just test that the methods exist and can be called without errors
  Cute::cf_push_font_size(12.0)
  Cute::cf_pop_font_size
  assert_true true
end

assert 'Cute::cf_text_width' do
  width = Cute::cf_text_width('test')
  assert_kind_of Float, width
end

assert 'Cute::cf_text_height' do
  height = Cute::cf_text_height('test')
  assert_kind_of Float, height
end

assert 'Cute::cf_text_size' do
  size = Cute::cf_text_size('test')
  assert_equal 'Cute::V2', size.class.to_s
end