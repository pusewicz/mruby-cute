#include "cute.h"
#include "mruby-cute.h"
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

static mrb_value mrb_cf_result_initialize(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = (CF_Sprite*) DATA_PTR(self);
  if (sprite) mrb_free(mrb, sprite);
  DATA_TYPE(self) = &mrb_cf_result_type;
  DATA_PTR(self) = mrb_malloc(mrb, sizeof(CF_Sprite));
  return self;
}

static mrb_value mrb_cf_is_error(mrb_state* mrb, mrb_value self)
{
  CF_Result result;
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);
  result = *(CF_Result*) DATA_PTR(arg);
  return mrb_bool_value(cf_is_error(result));
}

void mrb_cute_result_init(mrb_state* mrb, struct RClass* cute_module)
{
  // CF_Result
  struct RClass* cf_result_class = mrb_define_class_under(mrb, cute_module, "CF_Result", mrb->object_class);
  MRB_SET_INSTANCE_TT(cf_result_class, MRB_TT_DATA);

  mrb_define_method(mrb, cf_result_class, "initialize", mrb_cf_result_initialize, MRB_ARGS_NONE());

  // cute_result
  mrb_define_module_function(mrb, cute_module, "cf_is_error", mrb_cf_is_error, MRB_ARGS_REQ(1));
}
