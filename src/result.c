#include "cute.h"
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

static void mrb_cf_result_free(mrb_state* mrb, void* p)
{
  if (p) {
    mrb_free(mrb, p);
  }
}

static const struct mrb_data_type mrb_cf_result_type = {"CF_Result", mrb_cf_result_free};

static mrb_value mrb_cf_result_initialize(mrb_state* mrb, mrb_value self)
{
  CF_Result* result = (CF_Result*) DATA_PTR(self);
  if (result) {
    mrb_cf_result_free(mrb, result);
  }
  DATA_TYPE(self) = &mrb_cf_result_type;
  DATA_PTR(self) = NULL;

  mrb_int code;
  char* details = NULL;
  mrb_get_args(mrb, "i|z!", &code, &details);

  result = (CF_Result*) mrb_malloc(mrb, sizeof(CF_Result));
  result->code = code;
  result->details = details ? details : NULL;
  DATA_PTR(self) = result;

  return self;
}

static mrb_value mrb_cf_result_code(mrb_state* mrb, mrb_value self)
{
  CF_Result* result = DATA_PTR(self);
  return mrb_fixnum_value(result->code);
}

static mrb_value mrb_cf_result_details(mrb_state* mrb, mrb_value self)
{
  CF_Result* result = DATA_PTR(self);
  return result->details ? mrb_str_new_cstr(mrb, result->details) : mrb_nil_value();
}

static mrb_value mrb_cf_result_is_error(mrb_state* mrb, mrb_value self)
{
  CF_Result* result = DATA_PTR(self);
  return mrb_bool_value(result->code == CF_RESULT_ERROR);
}

static mrb_value mrb_cf_is_error(mrb_state* mrb, mrb_value self)
{
  CF_Result result;
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);
  result = *(CF_Result*) DATA_PTR(arg);
  return mrb_bool_value(cf_is_error(result));
}

mrb_value mrb_cf_result_from_cf_result(mrb_state* mrb, CF_Result result)
{
  struct RClass* cute_module = mrb_module_get(mrb, "Cute");
  struct RClass* result_class = mrb_class_get_under(mrb, cute_module, "Result");

  mrb_value args[2];
  args[0] = mrb_fixnum_value(result.code);
  args[1] = result.details ? mrb_str_new_cstr(mrb, result.details) : mrb_nil_value();

  return mrb_obj_new(mrb, result_class, 2, args);
}

void mrb_cute_result_init(mrb_state* mrb, struct RClass* cute_module)
{
  struct RClass* result_class = mrb_define_class_under(mrb, cute_module, "Result", mrb->object_class);
  MRB_SET_INSTANCE_TT(result_class, MRB_TT_DATA);

  mrb_define_method(mrb, result_class, "initialize", mrb_cf_result_initialize, MRB_ARGS_ARG(1, 1));
  mrb_define_method(mrb, result_class, "code", mrb_cf_result_code, MRB_ARGS_NONE());
  mrb_define_method(mrb, result_class, "details", mrb_cf_result_details, MRB_ARGS_NONE());
  mrb_define_method(mrb, result_class, "error?", mrb_cf_result_is_error, MRB_ARGS_NONE());

  mrb_define_module_function(mrb, cute_module, "is_error", mrb_cf_is_error, MRB_ARGS_REQ(1));
}
