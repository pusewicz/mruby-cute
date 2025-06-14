#include "vector.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>

static struct RClass* cV2;

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

    data = (CF_V2*)DATA_PTR(self);
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
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

void mrb_cute_v2_init(mrb_state* mrb, struct RClass* mCute)
{
    cV2 = mrb_define_class_under_id(mrb, mCute, MRB_SYM(V2), mrb->object_class);
    MRB_SET_INSTANCE_TT(cV2, MRB_TT_DATA);

    mrb_define_method_id(mrb, cV2, MRB_SYM(initialize), mrb_cf_v2_initialize, MRB_ARGS_OPT(2));
    mrb_define_method_id(mrb, cV2, MRB_SYM(x), mrb_cf_v2_get_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cV2, MRB_SYM_E(x), mrb_cf_v2_set_x, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cV2, MRB_SYM(y), mrb_cf_v2_get_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cV2, MRB_SYM_E(y), mrb_cf_v2_set_y, MRB_ARGS_REQ(1));
    mrb_define_module_function_id(mrb, mCute, MRB_SYM(V2), mrb_cf_v2_factory, MRB_ARGS_REQ(2));
}
