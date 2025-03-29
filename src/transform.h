#pragma once

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <cute.h>

struct RClass* cTransform;
struct mrb_data_type const mrb_cf_transform_data_type;

void mrb_cute_transform_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_transform_wrap(mrb_state *mrb, CF_Transform *transform);
