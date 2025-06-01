#pragma once

#include <cute.h>
#include <mruby.h>

void mrb_cute_result_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_result_wrap(mrb_state* mrb, CF_Result* result);
mrb_value mrb_cf_result_wrap_contained(mrb_state* mrb, CF_Result* result);
