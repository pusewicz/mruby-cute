#pragma once

#include <cute.h>
#include <mruby.h>

void mrb_cute_aabb_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_aabb_wrap(mrb_state* mrb, CF_Aabb* aabb);
CF_Aabb* mrb_cf_aabb_unwrap(mrb_state* mrb, mrb_value aabb);
