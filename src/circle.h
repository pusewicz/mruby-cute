#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct RClass* cCircle;
struct mrb_data_type const mrb_cf_circle_data_type;

void mrb_cute_circle_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_circle_wrap(mrb_state* mrb, CF_Circle* circle);
CF_Circle* mrb_cf_circle_unwrap(mrb_state* mrb, mrb_value circle);