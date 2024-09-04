#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>

static void mrb_v2_free(mrb_state* mrb, void* ptr)
{
  if (ptr) {
    mrb_free(mrb, ptr);
  }
}

static const struct mrb_data_type mrb_v2_type = {"V2", mrb_v2_free};

static mrb_value mrb_v2_initialize(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2 = (CF_V2*) DATA_PTR(self);
  if (v2) {
    mrb_v2_free(mrb, v2);
  }

  mrb_float x = 0, y = 0;
  mrb_get_args(mrb, "|ff", &x, &y);

  v2 = (CF_V2*) mrb_malloc(mrb, sizeof(CF_V2));
  *v2 = cf_v2(x, y);
  DATA_TYPE(self) = &mrb_v2_type;
  DATA_PTR(self) = v2;

  return self;
}

static mrb_value mrb_v2_x(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2 = DATA_PTR(self);
  return mrb_float_value(mrb, v2->x);
}

static mrb_value mrb_v2_y(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2 = DATA_PTR(self);
  return mrb_float_value(mrb, v2->y);
}

static mrb_value mrb_v2_set_x(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2 = DATA_PTR(self);
  mrb_float x;
  mrb_get_args(mrb, "f", &x);
  v2->x = x;
  return mrb_float_value(mrb, x);
}

static mrb_value mrb_v2_set_y(mrb_state* mrb, mrb_value self)
{
  CF_V2* v2 = DATA_PTR(self);
  mrb_float y;
  mrb_get_args(mrb, "f", &y);
  v2->y = y;
  return mrb_float_value(mrb, y);
}

static mrb_value mrb_v2_add(mrb_state* mrb, mrb_value self)
{
  mrb_value other;
  mrb_get_args(mrb, "o", &other);

  CF_V2* v1 = DATA_PTR(self);
  CF_V2* v2 = DATA_PTR(other);

  CF_V2 result = cf_add_v2(*v1, *v2);

  struct RClass* cute_module = mrb_module_get(mrb, "Cute");
  struct RClass* v2_class = mrb_class_get_under(mrb, cute_module, "V2");

  mrb_value new_v2 = mrb_obj_new(mrb, v2_class, 0, NULL);
  CF_V2* result_ptr = DATA_PTR(new_v2);
  *result_ptr = result;

  return new_v2;
}

void mrb_cute_math_init(mrb_state* mrb, struct RClass* cute_module)
{
  struct RClass* v2_class = mrb_define_class_under(mrb, cute_module, "V2", mrb->object_class);
  MRB_SET_INSTANCE_TT(v2_class, MRB_TT_DATA);

  mrb_define_method(mrb, v2_class, "initialize", mrb_v2_initialize, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, v2_class, "x", mrb_v2_x, MRB_ARGS_NONE());
  mrb_define_method(mrb, v2_class, "y", mrb_v2_y, MRB_ARGS_NONE());
  mrb_define_method(mrb, v2_class, "x=", mrb_v2_set_x, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v2_class, "y=", mrb_v2_set_y, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, v2_class, "+", mrb_v2_add, MRB_ARGS_REQ(1));
}
