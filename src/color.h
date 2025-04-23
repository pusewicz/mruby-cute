#pragma once

#include <cute.h>
#include <mruby.h>

struct RClass* cColor;
struct RClass* cPixel;

void mrb_cute_color_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_color_wrap(mrb_state* mrb, CF_Color* color);
CF_Color* mrb_cf_color_unwrap(mrb_state* mrb, mrb_value color);
mrb_value mrb_cf_pixel_wrap(mrb_state* mrb, CF_Pixel* pixel);
CF_Pixel* mrb_cf_pixel_unwrap(mrb_state* mrb, mrb_value pixel);
