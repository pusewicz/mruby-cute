#pragma once

#include <cute.h>
#include <mruby.h>

struct RClass* cSinCos;

void mrb_cute_sincos_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_sincos_wrap(mrb_state* mrb, CF_SinCos* sincos);
mrb_value mrb_cf_sincos_wrap_nested(mrb_state* mrb, CF_SinCos* sincos);
CF_SinCos* mrb_cf_sincos_unwrap(mrb_state* mrb, mrb_value self);
