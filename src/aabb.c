#include "aabb.h"
#include "vector.h"

#include <mruby/class.h>
#include <mruby/variable.h>

static struct RClass* cAabb;

static void mrb_cf_aabb_free(mrb_state* mrb, void* p)
{
    CF_Aabb* data = (CF_Aabb*)p;
    mrb_free(mrb, data);
}

const struct mrb_data_type mrb_cf_aabb_data_type = { "CF_Aabb", mrb_cf_aabb_free };

static mrb_value mrb_cf_aabb_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data;
    mrb_value min_obj, max_obj;

    mrb_get_args(mrb, "oo", &min_obj, &max_obj);

    CF_V2* min = mrb_cf_v2_unwrap(mrb, min_obj);
    CF_V2* max = mrb_cf_v2_unwrap(mrb, max_obj);

    data = (CF_Aabb*)mrb_malloc(mrb, sizeof(CF_Aabb));
    *data = cf_make_aabb(*min, *max);

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_aabb_data_type;

    return self;
}

static mrb_value mrb_cf_aabb_get_min(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = DATA_PTR(self);

    // Check if min iv is set
    mrb_sym iv_name = mrb_intern_lit(mrb, "min");
    mrb_value min_obj = mrb_iv_get(mrb, self, iv_name);
    if (!mrb_nil_p(min_obj)) {
        return min_obj;
    }

    // Create and reference a new min object
    min_obj = mrb_cf_v2_wrap_nested(mrb, &data->min);
    mrb_iv_set(mrb, self, iv_name, min_obj);
    mrb_iv_set(mrb, min_obj, mrb_intern_lit(mrb, "aabb"), self);

    return min_obj;
}

static mrb_value mrb_cf_aabb_set_min(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = (CF_Aabb*)DATA_PTR(self);
    mrb_value min_obj;
    mrb_get_args(mrb, "o", &min_obj);

    CF_V2* min = mrb_cf_v2_unwrap(mrb, min_obj);
    data->min = *min;

    return min_obj;
}

static mrb_value mrb_cf_aabb_get_max(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = DATA_PTR(self);

    // Check if max iv is set
    mrb_sym iv_name = mrb_intern_lit(mrb, "max");
    mrb_value max_obj = mrb_iv_get(mrb, self, iv_name);
    if (!mrb_nil_p(max_obj)) {
        return max_obj;
    }

    // Create and reference a new max object
    max_obj = mrb_cf_v2_wrap_nested(mrb, &data->max);
    mrb_iv_set(mrb, self, iv_name, max_obj);
    mrb_iv_set(mrb, max_obj, mrb_intern_lit(mrb, "aabb"), self);

    return max_obj;
}

static mrb_value mrb_cf_aabb_set_max(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = (CF_Aabb*)DATA_PTR(self);
    mrb_value max_obj;
    mrb_get_args(mrb, "o", &max_obj);

    CF_V2* max = mrb_cf_v2_unwrap(mrb, max_obj);
    data->max = *max;

    return max_obj;
}

static mrb_value mrb_cf_aabb_to_s(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = (CF_Aabb*)DATA_PTR(self);
    char buf[128];

    snprintf(buf, sizeof(buf), "Aabb(min=(%.3f, %.3f), max=(%.3f, %.3f))",
        data->min.x, data->min.y, data->max.x, data->max.y);
    return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_aabb_inspect(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data = (CF_Aabb*)DATA_PTR(self);
    char buf[128];

    snprintf(buf, sizeof(buf), "#<Cute::Aabb:0x%lx min=(%.3f, %.3f) max=(%.3f, %.3f)>",
        (unsigned long)data, data->min.x, data->min.y, data->max.x, data->max.y);
    return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_aabb_factory(mrb_state* mrb, mrb_value self)
{
    mrb_value min_obj, max_obj;
    CF_Aabb* data;

    mrb_get_args(mrb, "oo", &min_obj, &max_obj);

    CF_V2* min = mrb_cf_v2_unwrap(mrb, min_obj);
    CF_V2* max = mrb_cf_v2_unwrap(mrb, max_obj);

    data = (CF_Aabb*)mrb_malloc(mrb, sizeof(CF_Aabb));
    *data = cf_make_aabb(*min, *max);

    return mrb_cf_aabb_wrap(mrb, data);
}

mrb_value mrb_cf_aabb_wrap(mrb_state* mrb, CF_Aabb* aabb)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cAabb, &mrb_cf_aabb_data_type, aabb));
}

CF_Aabb* mrb_cf_aabb_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Aabb* data;

    data = (CF_Aabb*)DATA_PTR(self);
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
    }

    return data;
}

void mrb_cute_aabb_init(mrb_state* mrb, struct RClass* mCute)
{
    cAabb = mrb_define_class_under(mrb, mCute, "Aabb", mrb->object_class);
    MRB_SET_INSTANCE_TT(cAabb, MRB_TT_DATA);

    mrb_define_method(mrb, cAabb, "initialize", mrb_cf_aabb_initialize, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cAabb, "min", mrb_cf_aabb_get_min, MRB_ARGS_NONE());
    mrb_define_method(mrb, cAabb, "min=", mrb_cf_aabb_set_min, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cAabb, "max", mrb_cf_aabb_get_max, MRB_ARGS_NONE());
    mrb_define_method(mrb, cAabb, "max=", mrb_cf_aabb_set_max, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cAabb, "to_s", mrb_cf_aabb_to_s, MRB_ARGS_NONE());
    mrb_define_method(mrb, cAabb, "inspect", mrb_cf_aabb_inspect, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "Aabb", mrb_cf_aabb_factory, MRB_ARGS_REQ(2));
}
