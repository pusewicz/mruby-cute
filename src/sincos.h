#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

struct RClass* cSinCos;
struct mrb_data_type const mrb_cf_sincos_data_type;
struct mrb_data_type const mrb_cf_sincos_nested_data_type;

void mrb_cute_sincos_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_sincos_wrap(mrb_state* mrb, CF_SinCos* sincos);
mrb_value mrb_cf_sincos_wrap_nested(mrb_state* mrb, CF_SinCos* sincos);
