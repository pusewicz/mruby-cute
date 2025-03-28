#include "mrb_cute.h"

static mrb_value mrb_cf_make_app(mrb_state* mrb, mrb_value self)
{
  char* window_title = NULL;
  mrb_int display_id;
  mrb_int x;
  mrb_int y;
  mrb_int w;
  mrb_int h;
  mrb_int options;
  char* argv0;

  mrb_get_args(mrb, "ziiiiiiz", &window_title, &display_id, &x, &y, &w, &h, &options, &argv0);

  CF_Result* result_ptr = (CF_Result*) mrb_malloc(mrb, sizeof(CF_Result));
  *result_ptr = cf_make_app(window_title, display_id, x, y, w, h, options, argv0);
  struct RClass* cf_result_class = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_Result");
  return mrb_obj_value(Data_Wrap_Struct(mrb, cf_result_class, &mrb_cf_result_type, result_ptr));
}

static mrb_value mrb_cf_app_is_running(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_app_is_running());
}

static mrb_value mrb_cf_app_destroy(mrb_state* mrb, mrb_value self)
{
  cf_destroy_app();
  return mrb_nil_value();
}

static mrb_value mrb_cf_app_update(mrb_state* mrb, mrb_value self)
{
  // TODO: Add support for the OnUpdate callback.
  cf_app_update(NULL);
  return mrb_nil_value();
}

static mrb_value mrb_cf_default_display(mrb_state* mrb, mrb_value self)
{
  return mrb_fixnum_value(cf_default_display());
}

static mrb_value mrb_cf_app_draw_onto_screen(mrb_state* mrb, mrb_value self)
{
  mrb_bool clear_to_black = true;
  mrb_get_args(mrb, "|b", &clear_to_black);

  cf_app_draw_onto_screen(clear_to_black);
  return mrb_nil_value();
}

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mCute)
{
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_" #K, mrb_fixnum_value(V));
  CF_APP_OPTION_DEFS
  #undef CF_ENUM
  mrb_define_module_function(mrb, mCute, "cf_make_app", mrb_cf_make_app, MRB_ARGS_REQ(7));
  mrb_define_module_function(mrb, mCute, "cf_app_is_running", mrb_cf_app_is_running, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_app_destroy", mrb_cf_app_destroy, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_app_update", mrb_cf_app_update, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_default_display", mrb_cf_default_display, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_app_draw_onto_screen", mrb_cf_app_draw_onto_screen, MRB_ARGS_OPT(1));
}
