#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>

static mrb_value mrbcf_make_app(mrb_state* mrb, mrb_value self)
{
  const char* window_title = "Cute";
  CF_DisplayID display_id = cf_default_display();
  int x = 0;
  int y = 0;
  int w = 640;
  int h = 480;
  int options = 0;
  const char* argv0 = NULL;

  CF_Result result = cf_make_app(window_title, display_id, x, y, w, h, options, argv0);

  return mrb_cptr_value(mrb, &result);
}

static mrb_value mrbcf_app_is_running(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_app_is_running());
}

static mrb_value mrbcf_app_destroy(mrb_state* mrb, mrb_value self)
{
  cf_destroy_app();
  return mrb_nil_value();
}

static mrb_value mrbcf_app_update(mrb_state* mrb, mrb_value self)
{
  // TODO: Add support for the OnUpdate callback.
  cf_app_update(NULL);
  return mrb_nil_value();
}

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mrb_cute_module)
{
  DEFINE_MODULE_FUNCTION(make_app, MRB_ARGS_REQ(8));
  DEFINE_MODULE_FUNCTION(app_is_running, MRB_ARGS_NONE());
  DEFINE_MODULE_FUNCTION(app_destroy, MRB_ARGS_NONE());
  DEFINE_MODULE_FUNCTION(app_update, MRB_ARGS_NONE());
}
