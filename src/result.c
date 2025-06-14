#include "result.h"
#include <mruby/class.h>
#include <mruby/data.h>

void mrb_cf_result_free(mrb_state* mrb, void* p)
{
    CF_Result* result = (CF_Result*)p;
    mrb_free(mrb, result);
}

static const struct mrb_data_type mrb_cf_result_type = { "CF_Result", mrb_cf_result_free };
static const struct mrb_data_type mrb_cf_result_contained_type = { "CF_Result", NULL };

mrb_value mrb_cf_result_wrap(mrb_state* mrb, CF_Result* result)
{
    struct RClass* cResult = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_Result");
    return mrb_obj_value(Data_Wrap_Struct(mrb, cResult, &mrb_cf_result_type, result));
}

mrb_value mrb_cf_result_wrap_contained(mrb_state* mrb, CF_Result* result)
{
    struct RClass* cResult = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_Result");
    return mrb_obj_value(Data_Wrap_Struct(mrb, cResult, &mrb_cf_result_contained_type, result));
}

static mrb_value mrb_cf_result_initialize(mrb_state* mrb, mrb_value self)
{
    DATA_TYPE(self) = &mrb_cf_result_type;
    DATA_PTR(self) = mrb_malloc(mrb, sizeof(CF_Result));
    return self;
}

static mrb_value mrb_cf_is_error(mrb_state* mrb, mrb_value self)
{
    CF_Result result;
    mrb_value arg;
    mrb_get_args(mrb, "o", &arg);
    result = *(CF_Result*)DATA_PTR(arg);
    return mrb_bool_value(cf_is_error(result));
}

static mrb_value mrb_cf_result_error(mrb_state* mrb, mrb_value self)
{
    char const* details;
    mrb_get_args(mrb, "z", &details);
    CF_Result* result_ptr = (CF_Result*)mrb_malloc(mrb, sizeof(CF_Result));
    *result_ptr = cf_result_error(details);
    return mrb_cf_result_wrap(mrb, result_ptr);
}

static mrb_value mrb_cf_result_success(mrb_state* mrb, mrb_value self)
{
    CF_Result* result_ptr = (CF_Result*)mrb_malloc(mrb, sizeof(CF_Result));
    *result_ptr = cf_result_success();
    return mrb_cf_result_wrap(mrb, result_ptr);
}

void mrb_cute_result_init(mrb_state* mrb, struct RClass* mCute)
{
    // CF_Result
    struct RClass* cf_result_class = mrb_define_class_under(mrb, mCute, "CF_Result", mrb->object_class);
    MRB_SET_INSTANCE_TT(cf_result_class, MRB_TT_DATA);

    mrb_define_method(mrb, cf_result_class, "initialize", mrb_cf_result_initialize, MRB_ARGS_NONE());

    // cute_result
    mrb_define_module_function(mrb, mCute, "cf_is_error", mrb_cf_is_error, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_result_error", mrb_cf_result_error, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_result_success", mrb_cf_result_success, MRB_ARGS_NONE());
}
