module Cute
  # @method cf_make_font
  # @brief Creates a font from a file
  # @param [String] path The path to the font file
  # @param [String] font_name The unique name for this font
  # @return [Result] A result indicating success or failure
  def self.cf_make_font(path, font_name)
  end

  # @method cf_push_font
  # @brief Pushes a font to use for text drawing
  # @param [String] font_name The name of the font to use
  # @return [nil]
  def self.cf_push_font(font_name)
  end

  # @method cf_pop_font
  # @brief Pops the current font, returning to the previous font
  # @return [nil]
  def self.cf_pop_font
  end

  # @method cf_push_font_size
  # @brief Pushes a font size to use for text drawing
  # @param [Float] size The font size to use
  # @return [nil]
  def self.cf_push_font_size(size)
  end

  # @method cf_pop_font_size
  # @brief Pops the current font size, returning to the previous font size
  # @return [nil]
  def self.cf_pop_font_size
  end

  # @method cf_draw_text
  # @brief Draws text at the specified position
  # @param [String] text The text to draw
  # @param [V2] position The top-left corner of the text
  # @param [Integer] num_chars_to_draw (optional) The number of characters to draw. Use -1 to draw the whole string
  # @return [nil]
  def self.cf_draw_text(text, position, num_chars_to_draw = -1)
  end

  # @method cf_text_width
  # @brief Returns the width of a text given the currently pushed font
  # @param [String] text The text to measure
  # @param [Integer] num_chars_to_draw (optional) The number of characters to consider. Use -1 for the whole string
  # @return [Float] The width of the text in pixels
  def self.cf_text_width(text, num_chars_to_draw = -1)
  end

  # @method cf_text_height
  # @brief Returns the height of a text given the currently pushed font
  # @param [String] text The text to measure
  # @param [Integer] num_chars_to_draw (optional) The number of characters to consider. Use -1 for the whole string
  # @return [Float] The height of the text in pixels
  def self.cf_text_height(text, num_chars_to_draw = -1)
  end

  # @method cf_text_size
  # @brief Returns the size (width, height) of a text given the currently pushed font
  # @param [String] text The text to measure
  # @param [Integer] num_chars_to_draw (optional) The number of characters to consider. Use -1 for the whole string
  # @return [V2] The size of the text in pixels
  def self.cf_text_size(text, num_chars_to_draw = -1)
  end
end
