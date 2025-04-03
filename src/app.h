#pragma once

#include <cute.h>
#include <mruby.h>
#include <mruby/data.h>

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mCute);
