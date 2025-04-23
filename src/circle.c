#include "circle.h"
#include "vector.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>

struct RClass* cCircle;

static void mrb_cf_circle_free(mrb_state* mrb, void* p)
{
    CF_Circle* data = (CF_Circle*)p;
    mrb_free(mrb, data);
}

const struct mrb_data_type mrb_cf_circle_data_type = { "CF_Circle", mrb_cf_circle_free };

static mrb_value mrb_cf_circle_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data;
    mrb_value position;
    mrb_float radius;

    mrb_get_args(mrb, "of", &position, &radius);

    data = (CF_Circle*)mrb_malloc(mrb, sizeof(CF_Circle));
    data->p = *mrb_cf_v2_unwrap(mrb, position);
    data->r = (float)radius;

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_circle_data_type;

    return self;
}

static mrb_value mrb_cf_circle_get_position(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    CF_V2* position = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *position = data->p;
    return mrb_cf_v2_wrap(mrb, position);
}

static mrb_value mrb_cf_circle_set_position(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    mrb_value position;

    mrb_get_args(mrb, "o", &position);
    data->p = *mrb_cf_v2_unwrap(mrb, position);

    return position;
}

static mrb_value mrb_cf_circle_get_radius(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    return mrb_float_value(mrb, data->r);
}

static mrb_value mrb_cf_circle_set_radius(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    mrb_float radius;

    mrb_get_args(mrb, "f", &radius);
    data->r = (float)radius;

    return mrb_float_value(mrb, data->r);
}

static mrb_value mrb_cf_circle_to_s(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    char buf[64];

    snprintf(buf, sizeof(buf), "Circle(position=(%.3f, %.3f), radius=%.3f)", data->p.x, data->p.y, data->r);
    return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_circle_inspect(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data = (CF_Circle*)DATA_PTR(self);
    char buf[100];

    snprintf(buf, sizeof(buf), "#<Cute::Circle:0x%lx position=(%.3f, %.3f) radius=%.3f>",
        (unsigned long)data, data->p.x, data->p.y, data->r);
    return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_circle_wrap(mrb_state* mrb, CF_Circle* circle)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cCircle, &mrb_cf_circle_data_type, circle));
}

CF_Circle* mrb_cf_circle_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data;

    data = (CF_Circle*)DATA_PTR(self);
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized circle data");
    }

    return data;
}

static mrb_value mrb_cf_circle_factory(mrb_state* mrb, mrb_value self)
{
    CF_Circle* data;
    mrb_value position;
    mrb_float radius;

    mrb_get_args(mrb, "of", &position, &radius);

    data = (CF_Circle*)mrb_malloc(mrb, sizeof(CF_Circle));
    data->p = *mrb_cf_v2_unwrap(mrb, position);
    data->r = (float)radius;

    return mrb_cf_circle_wrap(mrb, data);
}

void mrb_cute_circle_init(mrb_state* mrb, struct RClass* mCute)
{
    cCircle = mrb_define_class_under(mrb, mCute, "Circle", mrb->object_class);
    MRB_SET_INSTANCE_TT(cCircle, MRB_TT_DATA);

    mrb_define_method_id(mrb, cCircle, MRB_SYM(initialize), mrb_cf_circle_initialize, MRB_ARGS_REQ(2));
    mrb_define_method_id(mrb, cCircle, MRB_SYM(position), mrb_cf_circle_get_position, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cCircle, MRB_SYM_E(position), mrb_cf_circle_set_position, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cCircle, MRB_SYM(radius), mrb_cf_circle_get_radius, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cCircle, MRB_SYM_E(radius), mrb_cf_circle_set_radius, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cCircle, MRB_SYM(to_s), mrb_cf_circle_to_s, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cCircle, MRB_SYM(inspect), mrb_cf_circle_inspect, MRB_ARGS_NONE());

    mrb_define_module_function_id(mrb, mCute, MRB_SYM(Circle), mrb_cf_circle_factory, MRB_ARGS_REQ(2));
}
