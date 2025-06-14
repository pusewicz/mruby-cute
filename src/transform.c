#include "transform.h"
#include "sincos.h"
#include "vector.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>
#include <mruby/variable.h>

static struct RClass* cTransform;

static void mrb_cf_transform_free(mrb_state* mrb, void* p)
{
    CF_Transform* data = (CF_Transform*)p;
    mrb_free(mrb, data);
}

struct mrb_data_type const mrb_cf_transform_data_type = {
    "CF_Transform",
    mrb_cf_transform_free,
};

struct mrb_data_type const mrb_cf_transform_contained_data_type = {
    "CF_Transform",
    NULL
};

static mrb_value mrb_cf_transform_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Transform* data;

    mrb_value p = mrb_nil_value();
    mrb_float r;

    mrb_get_args(mrb, "|of", &p, &r);

    data = (CF_Transform*)mrb_malloc(mrb, sizeof(CF_Transform));

    if (!mrb_nil_p(p) && r >= 0.0f) {
        CF_V2* v2 = mrb_cf_v2_unwrap(mrb, p);

        *data = cf_make_transform_TR(*v2, r);
    } else {
        *data = cf_make_transform();
    }

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_transform_data_type;

    return self;
}

mrb_value mrb_cf_transform_wrap(mrb_state* mrb, CF_Transform* transform)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cTransform, &mrb_cf_transform_data_type, transform));
}

mrb_value mrb_cf_transform_wrap_contained(mrb_state* mrb, CF_Transform* transform)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cTransform, &mrb_cf_transform_contained_data_type, transform));
}

static mrb_value mrb_cf_transform_get_p(mrb_state* mrb, mrb_value self)
{
    CF_Transform* transform = DATA_PTR(self);

    // Check if the V2 object is already set
    mrb_sym iv_name = mrb_intern_lit(mrb, "p");
    mrb_value p_obj = mrb_iv_get(mrb, self, iv_name);
    if (!mrb_nil_p(p_obj)) {
        return p_obj;
    }

    // Create a new V2 object
    p_obj = mrb_cf_v2_wrap_contained(mrb, &transform->p);
    mrb_iv_set(mrb, self, iv_name, p_obj);
    mrb_iv_set(mrb, p_obj, mrb_intern_lit(mrb, "transform"), self);

    return p_obj;
}

static mrb_value mrb_cf_transform_set_p(mrb_state* mrb, mrb_value self)
{
    CF_Transform* data = (CF_Transform*)DATA_PTR(self);
    mrb_value p;
    mrb_get_args(mrb, "o", &p);

    CF_V2* v2 = mrb_cf_v2_unwrap(mrb, p);
    data->p = *v2;

    return p;
}

// Get r as SinCos
static mrb_value mrb_cf_transform_get_r(mrb_state* mrb, mrb_value self)
{
    CF_Transform* data = DATA_PTR(self);

    // Check if the SinCos object is already set
    mrb_sym iv_name = mrb_intern_lit(mrb, "r");
    mrb_value r_obj = mrb_iv_get(mrb, self, iv_name);
    if (!mrb_nil_p(r_obj)) {
        return r_obj;
    }

    // Create a new SinCos object
    r_obj = mrb_cf_sincos_wrap_contained(mrb, &data->r);
    mrb_iv_set(mrb, self, iv_name, r_obj);
    mrb_iv_set(mrb, r_obj, mrb_intern_lit(mrb, "transform"), self);

    return r_obj;
}

// Set r as SinCos
static mrb_value mrb_cf_transform_set_r(mrb_state* mrb, mrb_value self)
{
    CF_Transform* data = (CF_Transform*)DATA_PTR(self);
    mrb_value r;
    mrb_get_args(mrb, "o", &r);

    data->r = *mrb_cf_sincos_unwrap(mrb, r);

    return r;
}

static mrb_value mrb_cf_transform_factory(mrb_state* mrb, mrb_value self)
{
    mrb_value p = mrb_nil_value();
    mrb_float r;
    CF_Transform* transform;

    mrb_get_args(mrb, "|of", &p, &r);

    transform = (CF_Transform*)mrb_malloc(mrb, sizeof(CF_Transform));

    if (!mrb_nil_p(p) && r >= 0.0f) {
        CF_V2* v2 = mrb_cf_v2_unwrap(mrb, p);

        *transform = cf_make_transform_TR(*v2, r);
    } else {
        *transform = cf_make_transform();
    }

    return mrb_cf_transform_wrap(mrb, transform);
}

void mrb_cute_transform_init(mrb_state* mrb, struct RClass* mCute)
{
    cTransform = mrb_define_class_under_id(mrb, mCute, MRB_SYM(Transform), mrb->object_class);
    MRB_SET_INSTANCE_TT(cTransform, MRB_TT_DATA);

    mrb_define_method_id(mrb, cTransform, MRB_SYM(initialize), mrb_cf_transform_initialize, MRB_ARGS_OPT(2));
    mrb_define_method_id(mrb, cTransform, MRB_SYM(p), mrb_cf_transform_get_p, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cTransform, MRB_SYM_E(p), mrb_cf_transform_set_p, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cTransform, MRB_SYM(r), mrb_cf_transform_get_r, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cTransform, MRB_SYM_E(r), mrb_cf_transform_set_r, MRB_ARGS_REQ(1));
    mrb_define_module_function_id(mrb, mCute, MRB_SYM(Transform), mrb_cf_transform_factory, MRB_ARGS_OPT(2));
}
