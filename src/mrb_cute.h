#ifndef MRB_CUTE_H
#define MRB_CUTE_H

#include <cute.h>
#include <mruby.h>
#if MRB_INT_BIT < 64
#error "need 64 bit mruby"
#endif
#include <mruby/variable.h>
#include <mruby/error.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>
// #include <mruby/array.h>
// #include <mruby/hash.h>
// #include <mruby/numeric.h>
// #include <mruby/throw.h>

static const struct mrb_data_type mrb_cf_result_type = {"CF_Result", mrb_free};
static const struct mrb_data_type mrb_cf_v2_type = {"CF_V2", mrb_free};

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_result_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_math_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_input_init(mrb_state* mrb, struct RClass* mrb_cute_module);

mrb_value mrb_cf_result_from_cf_result(mrb_state* mrb, CF_Result result);

#endif // MRB_CUTE_H
