#include "vector.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>

struct RClass* cV2;

static void mrb_cf_v2_free(mrb_state* mrb, void* p)
{
    CF_V2* data = (CF_V2*)p;
    mrb_free(mrb, data);
}

const struct mrb_data_type mrb_cf_v2_data_type = { "CF_V2", mrb_cf_v2_free };
const struct mrb_data_type mrb_cf_v2_contained_data_type = { "CF_V2", NULL };

static mrb_value mrb_cf_v2_initialize(mrb_state* mrb, mrb_value self)
{
    CF_V2* data;
    mrb_float x, y;

    mrb_get_args(mrb, "|ff", &x, &y);

    data = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *data = cf_v2(x, y);

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_v2_data_type;

    return self;
}

static mrb_value mrb_cf_v2_get_x(mrb_state* mrb, mrb_value self)
{
    CF_V2* data = DATA_PTR(self);
    return mrb_float_value(mrb, data->x);
}

static mrb_value mrb_cf_v2_set_x(mrb_state* mrb, mrb_value self)
{
    CF_V2* data = (CF_V2*)DATA_PTR(self);
    mrb_float x;
    mrb_get_args(mrb, "f", &x);
    data->x = x;
    return mrb_float_value(mrb, data->x);
}

static mrb_value mrb_cf_v2_get_y(mrb_state* mrb, mrb_value self)
{
    CF_V2* data = (CF_V2*)DATA_PTR(self);
    return mrb_float_value(mrb, data->y);
}

static mrb_value mrb_cf_v2_set_y(mrb_state* mrb, mrb_value self)
{
    CF_V2* data = (CF_V2*)DATA_PTR(self);
    mrb_float y;
    mrb_get_args(mrb, "f", &y);
    data->y = y;
    return mrb_float_value(mrb, data->y);
}

mrb_value mrb_cf_v2_wrap(mrb_state* mrb, CF_V2* v2)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cV2, &mrb_cf_v2_data_type, v2));
}

mrb_value mrb_cf_v2_wrap_contained(mrb_state* mrb, CF_V2* v2)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cV2, &mrb_cf_v2_contained_data_type, v2));
}

CF_V2* mrb_cf_v2_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_V2* data;

    // Type-safe unwrap - checks both data types
    data = (CF_V2*)mrb_data_get_ptr(mrb, self, &mrb_cf_v2_data_type);
    if (data == NULL) {
        // Try contained type
        data = (CF_V2*)mrb_data_get_ptr(mrb, self, &mrb_cf_v2_contained_data_type);
        if (data == NULL) {
            mrb_raisef(mrb, E_TYPE_ERROR, "expected %C, got %C",
                       cV2, mrb_obj_class(mrb, self));
        }
    }

    return data;
}

static mrb_value mrb_cf_v2_factory(mrb_state* mrb, mrb_value self)
{
    CF_V2* data;
    mrb_float x, y;

    mrb_get_args(mrb, "|ff", &x, &y);

    data = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *data = cf_v2(x, y);

    return mrb_cf_v2_wrap(mrb, data);
}

// Math operators
static mrb_value mrb_cf_v2_add(mrb_state* mrb, mrb_value self)
{
    CF_V2* v1 = mrb_cf_v2_unwrap(mrb, self);
    mrb_value other;
    mrb_get_args(mrb, "o", &other);
    CF_V2* v2 = mrb_cf_v2_unwrap(mrb, other);

    CF_V2* result = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *result = cf_add_v2(*v1, *v2);
    return mrb_cf_v2_wrap(mrb, result);
}

static mrb_value mrb_cf_v2_sub(mrb_state* mrb, mrb_value self)
{
    CF_V2* v1 = mrb_cf_v2_unwrap(mrb, self);
    mrb_value other;
    mrb_get_args(mrb, "o", &other);
    CF_V2* v2 = mrb_cf_v2_unwrap(mrb, other);

    CF_V2* result = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *result = cf_sub_v2(*v1, *v2);
    return mrb_cf_v2_wrap(mrb, result);
}

static mrb_value mrb_cf_v2_mul(mrb_state* mrb, mrb_value self)
{
    CF_V2* v = mrb_cf_v2_unwrap(mrb, self);
    mrb_float scalar;
    mrb_get_args(mrb, "f", &scalar);

    CF_V2* result = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *result = cf_mul_v2(*v, scalar);
    return mrb_cf_v2_wrap(mrb, result);
}

static mrb_value mrb_cf_v2_div(mrb_state* mrb, mrb_value self)
{
    CF_V2* v = mrb_cf_v2_unwrap(mrb, self);
    mrb_float scalar;
    mrb_get_args(mrb, "f", &scalar);

    CF_V2* result = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *result = cf_div_v2(*v, scalar);
    return mrb_cf_v2_wrap(mrb, result);
}

static mrb_value mrb_cf_v2_neg(mrb_state* mrb, mrb_value self)
{
    CF_V2* v = mrb_cf_v2_unwrap(mrb, self);

    CF_V2* result = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *result = cf_neg_v2(*v);
    return mrb_cf_v2_wrap(mrb, result);
}

void mrb_cute_v2_init(mrb_state* mrb, struct RClass* mCute)
{
    cV2 = mrb_define_class_under_id(mrb, mCute, MRB_SYM(V2), mrb->object_class);
    MRB_SET_INSTANCE_TT(cV2, MRB_TT_DATA);

    mrb_define_method_id(mrb, cV2, MRB_SYM(initialize), mrb_cf_v2_initialize, MRB_ARGS_OPT(2));
    mrb_define_method_id(mrb, cV2, MRB_SYM(x), mrb_cf_v2_get_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cV2, MRB_SYM_E(x), mrb_cf_v2_set_x, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_SYM(y), mrb_cf_v2_get_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cV2, MRB_SYM_E(y), mrb_cf_v2_set_y, MRB_ARGS_REQ(1));

    // Math operators
    mrb_define_method_id(mrb, cV2, MRB_OPSYM(add), mrb_cf_v2_add, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_OPSYM(sub), mrb_cf_v2_sub, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_OPSYM(mul), mrb_cf_v2_mul, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_OPSYM(div), mrb_cf_v2_div, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_OPSYM(minus), mrb_cf_v2_neg, MRB_ARGS_NONE());

    mrb_define_module_function_id(mrb, mCute, MRB_SYM(V2), mrb_cf_v2_factory, MRB_ARGS_REQ(2));
}
