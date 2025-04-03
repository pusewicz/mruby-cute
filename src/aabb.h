#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct RClass* cAabb;
struct mrb_data_type const mrb_cf_aabb_data_type;

void mrb_cute_aabb_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_aabb_wrap(mrb_state* mrb, CF_Aabb* aabb);
CF_Aabb* mrb_cf_aabb_unwrap(mrb_state* mrb, mrb_value aabb);
