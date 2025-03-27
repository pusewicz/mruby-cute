#include "vector.h"

extern struct RClass *cV2;

static void mrb_cf_v2_free(mrb_state *mrb, void *p) {
  mrb_free(mrb, p);
}

static mrb_value mrb_cf_v2_initialize(mrb_state *mrb, mrb_value self) {
  mrb_cf_v2_t *data;
  mrb_float x, y;

  mrb_get_args(mrb, "|ff", &x, &y);

  data = (mrb_cf_v2_t *)mrb_malloc(mrb, sizeof(mrb_cf_v2_t));
  data->v2 = cf_v2(x, y);

  DATA_PTR(self) = data;
  DATA_TYPE(self) = &mrb_cf_v2_data_type;

  return self;
}

static mrb_value mrb_cf_v2_get_x(mrb_state *mrb, mrb_value self) {
  mrb_cf_v2_t *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->v2.x);
}

static mrb_value mrb_cf_v2_set_x(mrb_state *mrb, mrb_value self) {
  mrb_cf_v2_t *data = DATA_PTR(self);
  mrb_float x;
  mrb_get_args(mrb, "f", &x);
  data->v2.x = x;
  return mrb_float_value(mrb, data->v2.x);
}

static mrb_value mrb_cf_v2_get_y(mrb_state *mrb, mrb_value self) {
  mrb_cf_v2_t *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->v2.y);
}

static mrb_value mrb_cf_v2_set_y(mrb_state *mrb, mrb_value self) {
  mrb_cf_v2_t *data = DATA_PTR(self);
  mrb_float y;
  mrb_get_args(mrb, "f", &y);
  data->v2.y = y;
  return mrb_float_value(mrb, data->v2.y);
}

static mrb_value mrb_cf_v2_to_s(mrb_state* mrb, mrb_value self)
{
  mrb_cf_v2_t *data = (mrb_cf_v2_t *)DATA_PTR(self);
  char buf[64];

  snprintf(buf, sizeof(buf), "V2(%.3f, %.3f)", data->v2.x, data->v2.y);
  return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_v2_inspect(mrb_state* mrb, mrb_value self)
{
  mrb_cf_v2_t *data = (mrb_cf_v2_t *)DATA_PTR(self);
  char buf[80];

  snprintf(buf, sizeof(buf), "#<Cute::V2:0x%lx x=%.3f y=%.3f>", (unsigned long)data, data->v2.x, data->v2.y);
  return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_v2_wrap(mrb_state *mrb, CF_V2 v2)
{
  mrb_cf_v2_t *data = (mrb_cf_v2_t *)mrb_malloc(mrb, sizeof(mrb_cf_v2_t));
  data->v2 = v2;

  return mrb_obj_value(Data_Wrap_Struct(mrb, cV2, &mrb_cf_v2_data_type, data));
}

CF_V2 mrb_cf_v2_unwrap(mrb_state *mrb, mrb_value self)
{
  mrb_cf_v2_t *data;

  data = (mrb_cf_v2_t*)mrb_data_get_ptr(mrb, self, &mrb_cf_v2_data_type);
  if (data == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  return data->v2;
}

static mrb_value mrb_cf_v2_factory(mrb_state* mrb, mrb_value self)
{
  mrb_float x, y;
  mrb_get_args(mrb, "ff", &x, &y);

  CF_V2 v2 = cf_v2(x, y);
  return mrb_cf_v2_wrap(mrb, v2);
}

void mrb_cute_v2_init(mrb_state* mrb, struct RClass* mCute) {
  cV2 = mrb_define_class_under(mrb, mCute, "V2", mrb->object_class);
  MRB_SET_INSTANCE_TT(cV2, MRB_TT_DATA);

  mrb_define_method(mrb, cV2, "initialize", mrb_cf_v2_initialize, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, cV2, "x", mrb_cf_v2_get_x, MRB_ARGS_NONE());
  mrb_define_method(mrb, cV2, "x=", mrb_cf_v2_set_x, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cV2, "y", mrb_cf_v2_get_y, MRB_ARGS_NONE());
  mrb_define_method(mrb, cV2, "y=", mrb_cf_v2_set_y, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cV2, "to_s", mrb_cf_v2_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cV2, "inspect", mrb_cf_v2_inspect, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "V2", mrb_cf_v2_factory, MRB_ARGS_REQ(2));
}
