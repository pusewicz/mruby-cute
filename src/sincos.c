#include "vector.h"

extern struct RClass *cSinCos;

static void mrb_cf_sincos_free(mrb_state *mrb, void *p) {
  // TODO: We should only free if the CF_SinCos was created as a new object
  // and not part of a transform struct as it's not dynamically allocated.
  CF_SinCos *data = (CF_SinCos *)p;
  mrb_free(mrb, data);
}

struct mrb_data_type const mrb_cf_sincos_data_type = {
  "CF_SinCos",
  mrb_cf_sincos_free,
};

static mrb_value mrb_cf_sincos_initialize(mrb_state *mrb, mrb_value self) {
  CF_SinCos *data;
  mrb_float r;

  mrb_get_args(mrb, "|f", &r);

  data = (CF_SinCos *)mrb_malloc(mrb, sizeof(CF_SinCos));
  if (r >= 0.0f) {
    *data = cf_sincos_f(r);
  } else {
    *data = cf_sincos();
  }

  DATA_PTR(self) = data;
  DATA_TYPE(self) = &mrb_cf_sincos_data_type;

  return self;
}

// Get s
static mrb_value mrb_cf_sincos_get_s(mrb_state *mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->s);
}

// Set s
static mrb_value mrb_cf_sincos_set_s(mrb_state *mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  mrb_float s;
  mrb_get_args(mrb, "f", &s);
  data->s = s;
  return mrb_float_value(mrb, data->s);
}

// Get c
static mrb_value mrb_cf_sincos_get_c(mrb_state *mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->c);
}

// Set c
static mrb_value mrb_cf_sincos_set_c(mrb_state *mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  mrb_float c;
  mrb_get_args(mrb, "f", &c);
  data->c = c;
  return mrb_float_value(mrb, data->c);
}

// to_s
static mrb_value mrb_cf_sincos_to_s(mrb_state* mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  char buf[64];
  snprintf(buf, sizeof(buf), "SinCos(s=%.3f c=%.3f)", data->s, data->c);
  return mrb_str_new_cstr(mrb, buf);
}

// inspect
static mrb_value mrb_cf_sincos_inspect(mrb_state* mrb, mrb_value self) {
  CF_SinCos *data = DATA_PTR(self);
  char buf[80];
  snprintf(buf, sizeof(buf), "#<Cute::SinCos:0x%lx s=%.3f c=%.3f>", (unsigned long)data, data->s, data->c);
  return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_sincos_wrap(mrb_state *mrb, CF_SinCos *sincos) {
  return mrb_obj_value(Data_Wrap_Struct(mrb, cSinCos, &mrb_cf_sincos_data_type, sincos));
}

static mrb_value mrb_cf_sincos_factory(mrb_state *mrb, mrb_value self) {
  mrb_float r;
  CF_SinCos *data;

  mrb_get_args(mrb, "|f", &r);

  data = (CF_SinCos *)mrb_malloc(mrb, sizeof(CF_SinCos));

  if (r >= 0.0f) {
    *data = cf_sincos_f(r);
  } else {
    *data = cf_sincos();
  }

  return mrb_cf_sincos_wrap(mrb, data);
}

void mrb_cute_sincos_init(mrb_state* mrb, struct RClass* mCute) {
  cSinCos = mrb_define_class_under(mrb, mCute, "SinCos", mrb->object_class);
  MRB_SET_INSTANCE_TT(cSinCos, MRB_TT_DATA);

  mrb_define_method(mrb, cSinCos, "initialize", mrb_cf_sincos_initialize, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, cSinCos, "s", mrb_cf_sincos_get_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cSinCos, "s=", mrb_cf_sincos_set_s, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cSinCos, "c", mrb_cf_sincos_get_c, MRB_ARGS_NONE());
  mrb_define_method(mrb, cSinCos, "c=", mrb_cf_sincos_set_c, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cSinCos, "to_s", mrb_cf_sincos_to_s, MRB_ARGS_NONE());
  mrb_define_method(mrb, cSinCos, "inspect", mrb_cf_sincos_inspect, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, mCute, "SinCos", mrb_cf_sincos_factory, MRB_ARGS_OPT(1));
}
