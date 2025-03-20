#include "cute.h"
#include <cute_color.h>

/**
 * Struct definitions
 */
static const struct mrb_data_type CF_Color_type = { "CF_Color", mrb_free };
static const struct mrb_data_type CF_Pixel_type = { "CF_Pixel", mrb_free };

/**
 * Data type definitions
 */
typedef struct mrb_cf_color_data_t {
  CF_Color* cf_color_ptr;
} mrb_cf_color_data_t;

typedef struct mrb_cf_pixel_data_t {
  CF_Pixel* cf_pixel_ptr;
} mrb_cf_pixel_data_t;


/**
 * Function wrapper declarations TODO: Move to header
 */
static mrb_value mrb_cf_abs_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_add_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_add_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_add_un8(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_color01(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_black(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_blue(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_brown(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_clear(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_cyan(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_green(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_grey(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_invisible(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_lerp(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_magenta(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_orange(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_premultiply(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_purple(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_red(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_to_int_rgb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_to_int_rgba(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_to_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_to_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_to_string(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_white(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_color_yellow(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_div_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_div_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_div_un8(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_fract_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_hsv_to_rgb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_hue(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_hex(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_hex2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_hex_string(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_rgb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_rgb_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_rgba(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_color_rgba_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_hex(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_hex_string(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_rgb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_rgb_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_rgba(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_pixel_rgba_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mod_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_color2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_un8(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_overlay(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_overlay_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_black(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_blue(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_brown(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_clear(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_cyan(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_green(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_grey(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_invisible(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_lerp(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_magenta(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_orange(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_premultiply(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_purple(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_red(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_to_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_to_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_to_int_rgb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_to_int_rgba(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_to_string(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_white(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_pixel_yellow(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_rgb_to_hsv(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_softlight(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_softlight_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_splat_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sub_color(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sub_pixel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sub_un8(mrb_state *mrb, mrb_value self);

/**
 * Function wrappers
 */
/*  */
static mrb_value mrb_cf_abs_color(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_Color c_a = mrb_cptr(a);

  CF_Color result = cf_abs_color(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_add_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Color c_a = mrb_cptr(a);
  CF_Color c_b = mrb_cptr(b);

  CF_Color result = cf_add_color(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_add_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Pixel c_a = mrb_cptr(a);
  CF_Pixel c_b = mrb_cptr(b);

  CF_Pixel result = cf_add_pixel(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_add_un8(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  int c_a = mrb_fixnum(a);
  int c_b = mrb_fixnum(b);

  uint8_t result = cf_add_un8(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_clamp_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, lo, hi;

  mrb_get_args(mrb, "ooo", &a, &lo, &hi);

  CF_Color c_a = mrb_cptr(a);
  CF_Color c_lo = mrb_cptr(lo);
  CF_Color c_hi = mrb_cptr(hi);

  CF_Color result = cf_clamp_color(c_a, c_lo, c_hi);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp_color01(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_Color c_a = mrb_cptr(a);

  CF_Color result = cf_clamp_color01(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_black(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_black();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_blue(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_blue();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_brown(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_brown();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_clear(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_clear();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_cyan(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_cyan();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_green(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_green();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_grey(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_grey();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_invisible(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_invisible();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_lerp(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, s;

  mrb_get_args(mrb, "ooo", &a, &b, &s);

  CF_Color c_a = mrb_cptr(a);
  CF_Color c_b = mrb_cptr(b);
  float c_s = mrb_float(s);

  CF_Color result = cf_color_lerp(c_a, c_b, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_magenta(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_magenta();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_orange(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_orange();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_premultiply(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  CF_Color result = cf_color_premultiply(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_purple(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_purple();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_red(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_red();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_to_int_rgb(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  uint32_t result = cf_color_to_int_rgb(c_c);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_color_to_int_rgba(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  uint32_t result = cf_color_to_int_rgba(c_c);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_color_to_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  CF_Pixel result = cf_color_to_pixel(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_to_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  CF_Pixel result = cf_color_to_pixel(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_to_string(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  char* result = cf_color_to_string(c_c);
  return mrb_str_new_cstr(result);
}
/*  */
static mrb_value mrb_cf_color_white(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_white();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_color_yellow(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Color result = cf_color_yellow();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_div_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, s;

  mrb_get_args(mrb, "oo", &a, &s);

  CF_Color c_a = mrb_cptr(a);
  float c_s = mrb_float(s);

  CF_Color result = cf_div_color(c_a, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_div_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value a, s;

  mrb_get_args(mrb, "oo", &a, &s);

  CF_Pixel c_a = mrb_cptr(a);
  uint8_t c_s = mrb_fixnum(s);

  CF_Pixel result = cf_div_pixel(c_a, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_div_un8(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  int c_a = mrb_fixnum(a);
  int c_b = mrb_fixnum(b);

  uint8_t result = cf_div_un8(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_fract_color(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_Color c_a = mrb_cptr(a);

  CF_Color result = cf_fract_color(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_hsv_to_rgb(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  CF_Color result = cf_hsv_to_rgb(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_hue(mrb_state *mrb, mrb_value self) {
  mrb_value base, tint;

  mrb_get_args(mrb, "oo", &base, &tint);

  CF_Color c_base = mrb_cptr(base);
  CF_Color c_tint = mrb_cptr(tint);

  CF_Color result = cf_hue(c_base, c_tint);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_hex(mrb_state *mrb, mrb_value self) {
  mrb_value hex;

  mrb_get_args(mrb, "o", &hex);

  int c_hex = mrb_fixnum(hex);

  CF_Color result = cf_make_color_hex(c_hex);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_hex2(mrb_state *mrb, mrb_value self) {
  mrb_value hex, alpha;

  mrb_get_args(mrb, "oo", &hex, &alpha);

  int c_hex = mrb_fixnum(hex);
  int c_alpha = mrb_fixnum(alpha);

  CF_Color result = cf_make_color_hex2(c_hex, c_alpha);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_hex_string(mrb_state *mrb, mrb_value self) {
  mrb_value hex;

  mrb_get_args(mrb, "o", &hex);

  const char* c_hex = mrb_str_to_cstr(mrb, hex);

  CF_Color result = cf_make_color_hex_string(c_hex);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_rgb(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b;

  mrb_get_args(mrb, "ooo", &r, &g, &b);

  uint8_t c_r = mrb_fixnum(r);
  uint8_t c_g = mrb_fixnum(g);
  uint8_t c_b = mrb_fixnum(b);

  CF_Color result = cf_make_color_rgb(c_r, c_g, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_rgb_f(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b;

  mrb_get_args(mrb, "ooo", &r, &g, &b);

  float c_r = mrb_float(r);
  float c_g = mrb_float(g);
  float c_b = mrb_float(b);

  CF_Color result = cf_make_color_rgb_f(c_r, c_g, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_rgba(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b, a;

  mrb_get_args(mrb, "oooo", &r, &g, &b, &a);

  uint8_t c_r = mrb_fixnum(r);
  uint8_t c_g = mrb_fixnum(g);
  uint8_t c_b = mrb_fixnum(b);
  uint8_t c_a = mrb_fixnum(a);

  CF_Color result = cf_make_color_rgba(c_r, c_g, c_b, c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_color_rgba_f(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b, a;

  mrb_get_args(mrb, "oooo", &r, &g, &b, &a);

  float c_r = mrb_float(r);
  float c_g = mrb_float(g);
  float c_b = mrb_float(b);
  float c_a = mrb_float(a);

  CF_Color result = cf_make_color_rgba_f(c_r, c_g, c_b, c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_hex(mrb_state *mrb, mrb_value self) {
  mrb_value hex;

  mrb_get_args(mrb, "o", &hex);

  int c_hex = mrb_fixnum(hex);

  CF_Pixel result = cf_make_pixel_hex(c_hex);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_hex_string(mrb_state *mrb, mrb_value self) {
  mrb_value hex;

  mrb_get_args(mrb, "o", &hex);

  const char* c_hex = mrb_str_to_cstr(mrb, hex);

  CF_Pixel result = cf_make_pixel_hex_string(c_hex);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_rgb(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b;

  mrb_get_args(mrb, "ooo", &r, &g, &b);

  uint8_t c_r = mrb_fixnum(r);
  uint8_t c_g = mrb_fixnum(g);
  uint8_t c_b = mrb_fixnum(b);

  CF_Pixel result = cf_make_pixel_rgb(c_r, c_g, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_rgb_f(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b;

  mrb_get_args(mrb, "ooo", &r, &g, &b);

  float c_r = mrb_float(r);
  float c_g = mrb_float(g);
  float c_b = mrb_float(b);

  CF_Pixel result = cf_make_pixel_rgb_f(c_r, c_g, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_rgba(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b, a;

  mrb_get_args(mrb, "oooo", &r, &g, &b, &a);

  uint8_t c_r = mrb_fixnum(r);
  uint8_t c_g = mrb_fixnum(g);
  uint8_t c_b = mrb_fixnum(b);
  uint8_t c_a = mrb_fixnum(a);

  CF_Pixel result = cf_make_pixel_rgba(c_r, c_g, c_b, c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_pixel_rgba_f(mrb_state *mrb, mrb_value self) {
  mrb_value r, g, b, a;

  mrb_get_args(mrb, "oooo", &r, &g, &b, &a);

  float c_r = mrb_float(r);
  float c_g = mrb_float(g);
  float c_b = mrb_float(b);
  float c_a = mrb_float(a);

  CF_Pixel result = cf_make_pixel_rgba_f(c_r, c_g, c_b, c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mod_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, m;

  mrb_get_args(mrb, "oo", &a, &m);

  CF_Color c_a = mrb_cptr(a);
  float c_m = mrb_float(m);

  CF_Color result = cf_mod_color(c_a, c_m);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, s;

  mrb_get_args(mrb, "oo", &a, &s);

  CF_Color c_a = mrb_cptr(a);
  float c_s = mrb_float(s);

  CF_Color result = cf_mul_color(c_a, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_color2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Color c_a = mrb_cptr(a);
  CF_Color c_b = mrb_cptr(b);

  CF_Color result = cf_mul_color2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value a, s;

  mrb_get_args(mrb, "oo", &a, &s);

  CF_Pixel c_a = mrb_cptr(a);
  uint8_t c_s = mrb_fixnum(s);

  CF_Pixel result = cf_mul_pixel(c_a, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_un8(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  int c_a = mrb_fixnum(a);
  int c_b = mrb_fixnum(b);

  uint8_t result = cf_mul_un8(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_overlay(mrb_state *mrb, mrb_value self) {
  mrb_value base, blend;

  mrb_get_args(mrb, "oo", &base, &blend);

  float c_base = mrb_float(base);
  float c_blend = mrb_float(blend);

  float result = cf_overlay(c_base, c_blend);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_overlay_color(mrb_state *mrb, mrb_value self) {
  mrb_value base, blend;

  mrb_get_args(mrb, "oo", &base, &blend);

  CF_Color c_base = mrb_cptr(base);
  CF_Color c_blend = mrb_cptr(blend);

  CF_Color result = cf_overlay_color(c_base, c_blend);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_black(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_black();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_blue(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_blue();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_brown(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_brown();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_clear(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_clear();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_cyan(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_cyan();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_green(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_green();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_grey(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_grey();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_invisible(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_invisible();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_lerp(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, s;

  mrb_get_args(mrb, "ooo", &a, &b, &s);

  CF_Pixel c_a = mrb_cptr(a);
  CF_Pixel c_b = mrb_cptr(b);
  float c_s = mrb_float(s);

  CF_Pixel result = cf_pixel_lerp(c_a, c_b, c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_magenta(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_magenta();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_orange(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_orange();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_premultiply(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Pixel c_c = mrb_cptr(c);

  CF_Pixel result = cf_pixel_premultiply(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_purple(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_purple();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_red(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_red();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_to_color(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Pixel c_p = mrb_cptr(p);

  CF_Color result = cf_pixel_to_color(c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_to_color(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Pixel c_p = mrb_cptr(p);

  CF_Color result = cf_pixel_to_color(c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_to_int_rgb(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Pixel c_p = mrb_cptr(p);

  uint32_t result = cf_pixel_to_int_rgb(c_p);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_pixel_to_int_rgba(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Pixel c_p = mrb_cptr(p);

  uint32_t result = cf_pixel_to_int_rgba(c_p);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_pixel_to_string(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Pixel c_p = mrb_cptr(p);

  char* result = cf_pixel_to_string(c_p);
  return mrb_str_new_cstr(result);
}
/*  */
static mrb_value mrb_cf_pixel_white(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_white();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_pixel_yellow(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Pixel result = cf_pixel_yellow();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_rgb_to_hsv(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Color c_c = mrb_cptr(c);

  CF_Color result = cf_rgb_to_hsv(c_c);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_softlight(mrb_state *mrb, mrb_value self) {
  mrb_value base, blend;

  mrb_get_args(mrb, "oo", &base, &blend);

  float c_base = mrb_float(base);
  float c_blend = mrb_float(blend);

  float result = cf_softlight(c_base, c_blend);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_softlight_color(mrb_state *mrb, mrb_value self) {
  mrb_value base, blend;

  mrb_get_args(mrb, "oo", &base, &blend);

  CF_Color c_base = mrb_cptr(base);
  CF_Color c_blend = mrb_cptr(blend);

  CF_Color result = cf_softlight_color(c_base, c_blend);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_splat_color(mrb_state *mrb, mrb_value self) {
  mrb_value v;

  mrb_get_args(mrb, "o", &v);

  float c_v = mrb_float(v);

  CF_Color result = cf_splat_color(c_v);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sub_color(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Color c_a = mrb_cptr(a);
  CF_Color c_b = mrb_cptr(b);

  CF_Color result = cf_sub_color(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sub_pixel(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Pixel c_a = mrb_cptr(a);
  CF_Pixel c_b = mrb_cptr(b);

  CF_Pixel result = cf_sub_pixel(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sub_un8(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  int c_a = mrb_fixnum(a);
  int c_b = mrb_fixnum(b);

  uint8_t result = cf_sub_un8(c_a, c_b);
  return mrb_fixnum_value(result);
}
CF_Color* mrb_cf_color_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_color_data_t* data = (mrb_cf_color_data_t*) DATA_PTR(self);
    return data->cf_color_ptr;
}

CF_Pixel* mrb_cf_pixel_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_pixel_data_t* data = (mrb_cf_pixel_data_t*) DATA_PTR(self);
    return data->cf_pixel_ptr;
}


/**
 * Initialize the module
 */
void mrb_mruby_cute_cute_color_gem_init(mrb_state *mrb, struct RClass *mCute)
{
  // Define enums
  

  // Define enum def definitions
  

  // Define functions
  mrb_define_module_function(mrb, mCute, "cf_abs_color", mrb_cf_abs_color, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_add_color", mrb_cf_add_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_add_pixel", mrb_cf_add_pixel, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_add_un8", mrb_cf_add_un8, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_clamp_color", mrb_cf_clamp_color, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_clamp_color01", mrb_cf_clamp_color01, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_black", mrb_cf_color_black, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_blue", mrb_cf_color_blue, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_brown", mrb_cf_color_brown, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_clear", mrb_cf_color_clear, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_cyan", mrb_cf_color_cyan, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_green", mrb_cf_color_green, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_grey", mrb_cf_color_grey, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_invisible", mrb_cf_color_invisible, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_lerp", mrb_cf_color_lerp, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_color_magenta", mrb_cf_color_magenta, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_orange", mrb_cf_color_orange, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_premultiply", mrb_cf_color_premultiply, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_purple", mrb_cf_color_purple, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_red", mrb_cf_color_red, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_to_int_rgb", mrb_cf_color_to_int_rgb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_to_int_rgba", mrb_cf_color_to_int_rgba, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_to_pixel", mrb_cf_color_to_pixel, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_to_pixel", mrb_cf_color_to_pixel, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_to_string", mrb_cf_color_to_string, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_color_white", mrb_cf_color_white, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_color_yellow", mrb_cf_color_yellow, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_div_color", mrb_cf_div_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_div_pixel", mrb_cf_div_pixel, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_div_un8", mrb_cf_div_un8, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_fract_color", mrb_cf_fract_color, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_hsv_to_rgb", mrb_cf_hsv_to_rgb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_hue", mrb_cf_hue, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_color_hex", mrb_cf_make_color_hex, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_color_hex2", mrb_cf_make_color_hex2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_color_hex_string", mrb_cf_make_color_hex_string, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_color_rgb", mrb_cf_make_color_rgb, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_color_rgb_f", mrb_cf_make_color_rgb_f, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_color_rgba", mrb_cf_make_color_rgba, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_make_color_rgba_f", mrb_cf_make_color_rgba_f, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_hex", mrb_cf_make_pixel_hex, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_hex_string", mrb_cf_make_pixel_hex_string, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_rgb", mrb_cf_make_pixel_rgb, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_rgb_f", mrb_cf_make_pixel_rgb_f, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_rgba", mrb_cf_make_pixel_rgba, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_make_pixel_rgba_f", mrb_cf_make_pixel_rgba_f, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_mod_color", mrb_cf_mod_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_color", mrb_cf_mul_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_color2", mrb_cf_mul_color2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_pixel", mrb_cf_mul_pixel, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_un8", mrb_cf_mul_un8, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_overlay", mrb_cf_overlay, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_overlay_color", mrb_cf_overlay_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_pixel_black", mrb_cf_pixel_black, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_blue", mrb_cf_pixel_blue, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_brown", mrb_cf_pixel_brown, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_clear", mrb_cf_pixel_clear, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_cyan", mrb_cf_pixel_cyan, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_green", mrb_cf_pixel_green, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_grey", mrb_cf_pixel_grey, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_invisible", mrb_cf_pixel_invisible, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_lerp", mrb_cf_pixel_lerp, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_pixel_magenta", mrb_cf_pixel_magenta, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_orange", mrb_cf_pixel_orange, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_premultiply", mrb_cf_pixel_premultiply, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_purple", mrb_cf_pixel_purple, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_red", mrb_cf_pixel_red, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_to_color", mrb_cf_pixel_to_color, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_to_color", mrb_cf_pixel_to_color, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_to_int_rgb", mrb_cf_pixel_to_int_rgb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_to_int_rgba", mrb_cf_pixel_to_int_rgba, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_to_string", mrb_cf_pixel_to_string, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_pixel_white", mrb_cf_pixel_white, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_pixel_yellow", mrb_cf_pixel_yellow, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_rgb_to_hsv", mrb_cf_rgb_to_hsv, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_softlight", mrb_cf_softlight, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_softlight_color", mrb_cf_softlight_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_splat_color", mrb_cf_splat_color, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sub_color", mrb_cf_sub_color, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_sub_pixel", mrb_cf_sub_pixel, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_sub_un8", mrb_cf_sub_un8, MRB_ARGS_REQ(2));
}
