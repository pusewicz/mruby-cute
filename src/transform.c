#include "cute_math.h"
#include "vector.h"
#include "sincos.h"

extern struct RClass *cTransform;

static void mrb_cf_transform_free(mrb_state *mrb, void *p) {
  mrb_free(mrb, p);
}

struct mrb_data_type const mrb_cf_transform_data_type = {
  "mrb_cf_transform_t",
  mrb_cf_transform_free,
};

typedef struct {
  CF_Transform transform;
} mrb_cf_transform_t;

static mrb_value mrb_cf_transform_initialize(mrb_state *mrb, mrb_value self) {
  mrb_cf_transform_t *data;

  mrb_value p = mrb_nil_value();
  mrb_float r;

  mrb_get_args(mrb, "|of", &p, &r);

  data = (mrb_cf_transform_t *)mrb_malloc(mrb, sizeof(mrb_cf_transform_t));

  if (!mrb_nil_p(p) && r >= 0.0f) {
    CF_V2 v2 = mrb_cf_v2_unwrap(mrb, p);

    data->transform = cf_make_transform_TR(v2, r);
  } else {
    data->transform = cf_make_transform();
  }

  DATA_PTR(self) = data;
  DATA_TYPE(self) = &mrb_cf_transform_data_type;

  return self;
}

mrb_value mrb_cf_transform_wrap(mrb_state *mrb, CF_Transform transform) {
  mrb_cf_transform_t *data;
  mrb_value obj;

  data = (mrb_cf_transform_t *)mrb_malloc(mrb, sizeof(mrb_cf_transform_t));
  data->transform = transform;

  obj = mrb_obj_value(Data_Wrap_Struct(mrb, cTransform, &mrb_cf_transform_data_type, data));

  return obj;
}

// Get p as a V2
static mrb_value mrb_cf_transform_get_p(mrb_state *mrb, mrb_value self) {
  mrb_cf_transform_t *data = DATA_PTR(self);

  return mrb_cf_v2_wrap(mrb, data->transform.p);
}

// Set p as a V2
static mrb_value mrb_cf_transform_set_p(mrb_state *mrb, mrb_value self) {
  mrb_cf_transform_t *data = DATA_PTR(self);
  mrb_value p;
  mrb_get_args(mrb, "o", &p);

  data->transform.p = *DATA_GET_PTR(mrb, p, &mrb_cf_v2_data_type, CF_V2);

  return mrb_cf_v2_wrap(mrb, data->transform.p);
}

// Get r as SinCos
static mrb_value mrb_cf_transform_get_r(mrb_state *mrb, mrb_value self) {
  mrb_cf_transform_t *data = DATA_PTR(self);

  return mrb_cf_sincos_wrap(mrb, data->transform.r);
}

// Set r as SinCos
static mrb_value mrb_cf_transform_set_r(mrb_state *mrb, mrb_value self) {
  mrb_cf_transform_t *data = DATA_PTR(self);
  mrb_value r;
  mrb_get_args(mrb, "o", &r);

  data->transform.r = *DATA_GET_PTR(mrb, r, &mrb_cf_sincos_data_type, CF_SinCos);

  return mrb_cf_sincos_wrap(mrb, data->transform.r);
}

static mrb_value mrb_cf_transform_factory(mrb_state *mrb, mrb_value self) {
  mrb_value p = mrb_nil_value();
  mrb_float r;
  CF_Transform transform;

  mrb_get_args(mrb, "|of", &p, &r);

  if (!mrb_nil_p(p) && r >= 0.0f) {
    CF_V2 v2 = mrb_cf_v2_unwrap(mrb, p);

    transform = cf_make_transform_TR(v2, r);
  } else {
    transform = cf_make_transform();
  }

  return mrb_cf_transform_wrap(mrb, transform);
}

void mrb_cute_transform_init(mrb_state* mrb, struct RClass* mCute) {
  cTransform = mrb_define_class_under(mrb, mCute, "Transform", mrb->object_class);
  MRB_SET_INSTANCE_TT(cTransform, MRB_TT_DATA);

  mrb_define_method(mrb, cTransform, "initialize", mrb_cf_transform_initialize, MRB_ARGS_OPT(2));
  mrb_define_method(mrb, cTransform, "p", mrb_cf_transform_get_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, cTransform, "p=", mrb_cf_transform_set_p, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cTransform, "r", mrb_cf_transform_get_r, MRB_ARGS_NONE());
  mrb_define_method(mrb, cTransform, "r=", mrb_cf_transform_set_r, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "Transform", mrb_cf_transform_factory, MRB_ARGS_OPT(2));
}
