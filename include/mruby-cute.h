#pragma once
#include <mruby.h>

#define DEFINE_MODULE_FUNCTION(name, args) mrb_define_module_function(mrb, mrb_cute_module, #name, mrbcf_##name, args)
#define DEFINE_MODULE_CONSTANT(name) mrb_define_const(mrb, mrb_cute_module, #name, mrb_fixnum_value(CF_##name))

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mrb_cute_module);
void mrb_cute_utility_init(mrb_state* mrb, struct RClass* mrb_cute_module);
