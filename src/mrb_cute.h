#ifndef MRB_CUTE_H
#define MRB_CUTE_H

#include <cute.h>
#include <mruby.h>
#if MRB_INT_BIT < 64
#error "need 64 bit mruby"
#endif
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/error.h>
#include <mruby/string.h>
#include <mruby/variable.h>

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mCute);
void mrb_cute_result_init(mrb_state* mrb, struct RClass* mCute);
void mrb_cute_input_init(mrb_state* mrb, struct RClass* mCute);
void mrb_cute_time_init(mrb_state* mrb, struct RClass* mCute);
void mrb_cute_stopwatch_init(mrb_state* mrb, struct RClass* mCute);
void mrb_cute_color_init(mrb_state* mrb, struct RClass* mCute);

mrb_value mrb_cf_result_from_cf_result(mrb_state* mrb, CF_Result result);

#endif // MRB_CUTE_H
