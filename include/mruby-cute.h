#pragma once
#include <cute.h>
#include <mruby.h>
#include <mruby/data.h>

static const struct mrb_data_type mrb_cf_result_type = {"CF_Result", mrb_free};

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_result_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_math_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mrb_cute_module);

mrb_value mrb_cf_result_from_cf_result(mrb_state* mrb, CF_Result result);
