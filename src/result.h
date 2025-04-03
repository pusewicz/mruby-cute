#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

void mrb_cute_result_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_result_wrap(mrb_state* mrb, CF_Result* result);
