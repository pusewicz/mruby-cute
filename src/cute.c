#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>

#define DEFINE_MODULE_FUNCTION(name, args) mrb_define_module_function(mrb, mrb_cute_module, #name, mrbcf_##name, args)

struct RClass* mrb_cute_module;

static mrb_value mrbcf_version_string_linked(mrb_state* mrb, mrb_value self)
{
  return mrb_str_new_cstr(mrb, cf_version_string_linked());
}

static void mrb_cute_init(mrb_state* mrb, struct RClass* mrb_cute_module)
{
  DEFINE_MODULE_FUNCTION(version_string_linked, MRB_ARGS_NONE());
}

void mrb_mruby_cute_gem_init(mrb_state* mrb)
{
  struct RClass* mrb_cute_module = mrb_define_module(mrb, "Cute");

  mrb_cute_init(mrb, mrb_cute_module);
}

void mrb_mruby_cute_gem_final(mrb_state* mrb)
{
}
