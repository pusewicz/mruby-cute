#include "vector.h"

extern struct RClass *cSinCos;

static void mrb_cf_sincos_free(mrb_state *mrb, void *p) {
  mrb_free(mrb, p);
}

struct mrb_data_type const mrb_cf_sincos_data_type = {
  "mrb_cf_sincos_t",
  mrb_cf_sincos_free,
};

typedef struct {
  CF_SinCos sincos;
} mrb_cf_sincos_t;

static mrb_value mrb_cf_sincos_initialize(mrb_state *mrb, mrb_value self) {
  mrb_cf_sincos_t *data;
  mrb_float r;

  mrb_get_args(mrb, "|f", &r);

  data = (mrb_cf_sincos_t *)mrb_malloc(mrb, sizeof(mrb_cf_sincos_t));
  if (r >= 0.0f) {
    data->sincos = cf_sincos_f(r);
  } else {
    data->sincos = cf_sincos();
  }

  DATA_PTR(self) = data;
  DATA_TYPE(self) = &mrb_cf_sincos_data_type;

  return self;
}

// Get s
static mrb_value mrb_cf_sincos_get_s(mrb_state *mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->sincos.s);
}

// Set s
static mrb_value mrb_cf_sincos_set_s(mrb_state *mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  mrb_float s;
  mrb_get_args(mrb, "f", &s);
  data->sincos.s = s;
  return mrb_float_value(mrb, data->sincos.s);
}

// Get c
static mrb_value mrb_cf_sincos_get_c(mrb_state *mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  return mrb_float_value(mrb, data->sincos.c);
}

// Set c
static mrb_value mrb_cf_sincos_set_c(mrb_state *mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  mrb_float c;
  mrb_get_args(mrb, "f", &c);
  data->sincos.c = c;
  return mrb_float_value(mrb, data->sincos.c);
}

// to_s
static mrb_value mrb_cf_sincos_to_s(mrb_state* mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  char buf[64];
  snprintf(buf, sizeof(buf), "SinCos(s=%.3f c=%.3f)", data->sincos.s, data->sincos.c);
  return mrb_str_new_cstr(mrb, buf);
}

// inspect
static mrb_value mrb_cf_sincos_inspect(mrb_state* mrb, mrb_value self) {
  mrb_cf_sincos_t *data = DATA_PTR(self);
  char buf[80];
  snprintf(buf, sizeof(buf), "#<Cute::SinCos:0x%lx s=%.3f c=%.3f>", (unsigned long)data, data->sincos.s, data->sincos.c);
  return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_sincos_wrap(mrb_state *mrb, CF_SinCos sincos) {
  mrb_cf_sincos_t *data;
  mrb_value obj;

  data = (mrb_cf_sincos_t *)mrb_malloc(mrb, sizeof(mrb_cf_sincos_t));
  data->sincos = sincos;

  obj = mrb_obj_value(Data_Wrap_Struct(mrb, cSinCos, &mrb_cf_sincos_data_type, data));

  return obj;
}

static mrb_value mrb_cf_sincos_factory(mrb_state *mrb, mrb_value self) {
  mrb_float r;
  CF_SinCos sincos;

  mrb_get_args(mrb, "|f", &r);

  if (r >= 0.0f) {
    sincos = cf_sincos_f(r);
  } else {
    sincos = cf_sincos();
  }

  return mrb_cf_sincos_wrap(mrb, sincos);
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
