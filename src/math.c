#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

static mrb_value mrb_cf_v2_initialize(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2_ptr = (CF_V2*) DATA_PTR(self);
  if (v2_ptr) mrb_free(mrb, v2_ptr);
  DATA_TYPE(self) = &mrb_cf_v2_type;
  DATA_PTR(self) = mrb_malloc(mrb, sizeof(CF_V2));
  return self;
}

static mrb_value mrb_cf_v2_get_x(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2_ptr = (CF_V2*) DATA_PTR(self);
  return mrb_float_value(mrb, v2_ptr->x);
}

static mrb_value mrb_cf_v2_get_y(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2_ptr = (CF_V2*) DATA_PTR(self);
  return mrb_float_value(mrb, v2_ptr->y);
}

static mrb_value mrb_cf_v2_set_x(mrb_state* mrb, mrb_value self)
{
  mrb_float x;
  mrb_get_args(mrb, "f", &x);
  CF_V2* v2_ptr = (CF_V2*) DATA_PTR(self);
  v2_ptr->x = x;
  return mrb_nil_value();
}

static mrb_value mrb_cf_v2_set_y(mrb_state* mrb, mrb_value self)
{
  mrb_float y;
  mrb_get_args(mrb, "f", &y);
  CF_V2* v2_ptr = (CF_V2*) DATA_PTR(self);
  v2_ptr->y = y;
  return mrb_nil_value();
}

static mrb_value mrb_cf_v2(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y;
  mrb_get_args(mrb, "ff", &x, &y);
  CF_V2* v2_ptr = (CF_V2*) mrb_malloc(mrb, sizeof(CF_V2));
  *v2_ptr = cf_v2(x, y);
  struct RClass* v2_class = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_V2");
  return mrb_obj_value(Data_Wrap_Struct(mrb, v2_class, &mrb_cf_v2_type, v2_ptr));
}

void mrb_cute_math_init(mrb_state* mrb, struct RClass* cute_module)
{
  // CF_V2
  struct RClass* v2_class = mrb_define_class_under(mrb, cute_module, "CF_V2", mrb->object_class);
  MRB_SET_INSTANCE_TT(v2_class, MRB_TT_DATA);

  mrb_define_method(mrb, v2_class, "initialize", mrb_cf_v2_initialize, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, v2_class, "x", mrb_cf_v2_get_x, MRB_ARGS_NONE());
  mrb_define_method(mrb, v2_class, "x=", mrb_cf_v2_set_x, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v2_class, "y", mrb_cf_v2_get_y, MRB_ARGS_NONE());
  mrb_define_method(mrb, v2_class, "y=", mrb_cf_v2_set_y, MRB_ARGS_REQ(1));

  // cute_math
  mrb_define_module_function(mrb, cute_module, "cf_v2", mrb_cf_v2, MRB_ARGS_REQ(2));
}
