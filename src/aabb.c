#include "aabb.h"
#include "vector.h"

extern struct RClass* cAabb;

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
    CF_V2* min = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *min = data->min;
    return mrb_cf_v2_wrap(mrb, min);
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
    CF_Aabb* data = (CF_Aabb*)DATA_PTR(self);
    CF_V2* max = (CF_V2*)mrb_malloc(mrb, sizeof(CF_V2));
    *max = data->max;
    return mrb_cf_v2_wrap(mrb, max);
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
