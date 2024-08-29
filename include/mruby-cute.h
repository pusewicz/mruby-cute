#pragma once
#include <mruby.h>

#define DEFINE_MODULE_FUNCTION(name, args) mrb_define_module_function(mrb, mrb_cute_module, #name, mrbcf_##name, args)

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mrb_cute_module);
