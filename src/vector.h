#pragma once

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <cute.h>

struct RClass* cV2;
struct mrb_data_type const mrb_cf_v2_data_type;
typedef struct mrb_cf_v2_t {
  CF_V2 v2;
} mrb_cf_v2_t;

void mrb_cute_v2_init(mrb_state* mrb, struct RClass* mCute);
mrb_value mrb_cf_v2_wrap(mrb_state *mrb, CF_V2 v2);
CF_V2 mrb_cf_v2_unwrap(mrb_state *mrb, mrb_value v2);
