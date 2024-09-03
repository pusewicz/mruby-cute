#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>

// cf_is_error
static mrb_value mrbcf_is_error(mrb_state* mrb, mrb_value self)
{
  CF_Result result;
  mrb_get_args(mrb, "I", &result);
  return mrb_bool_value(cf_is_error(result));
}
// cf_result_success
static mrb_value mrbcf_result_success(mrb_state* mrb, mrb_value self)
{
  //TODO: malloc
  CF_Result result = cf_result_success();
  return mrb_cptr_value(mrb, &result);
}

// cf_result_error
static mrb_value mrbcf_result_error(mrb_state* mrb, mrb_value self)
{
  const char* details;
  mrb_get_args(mrb, "z", &details);

  CF_Result result = cf_result_error(details);
  return mrb_cptr_value(mrb, &result);
}

void mrb_cute_utility_init(mrb_state* mrb, struct RClass* mrb_cute_module)
{
  DEFINE_MODULE_FUNCTION(is_error, MRB_ARGS_REQ(1));
  DEFINE_MODULE_FUNCTION(result_success, MRB_ARGS_NONE());
  DEFINE_MODULE_FUNCTION(result_error, MRB_ARGS_REQ(1));
}
