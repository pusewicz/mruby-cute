#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct RClass* cColor;
struct RClass* cPixel;
struct mrb_data_type const mrb_cf_color_data_type;
struct mrb_data_type const mrb_cf_pixel_data_type;

void mrb_cute_color_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_color_wrap(mrb_state* mrb, CF_Color* color);
CF_Color* mrb_cf_color_unwrap(mrb_state* mrb, mrb_value color);
mrb_value mrb_cf_pixel_wrap(mrb_state* mrb, CF_Pixel* pixel);
CF_Pixel* mrb_cf_pixel_unwrap(mrb_state* mrb, mrb_value pixel);