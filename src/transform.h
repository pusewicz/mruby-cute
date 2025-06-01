#pragma once

#include <cute.h>
#include <mruby.h>

void mrb_cute_transform_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_transform_wrap(mrb_state* mrb, CF_Transform* transform);
mrb_value mrb_cf_transform_wrap_contained(mrb_state* mrb, CF_Transform* transform);
