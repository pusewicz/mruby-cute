// Include CuteFramework headers
#include <cute_app.h>
#include <cute_color.h>
#include <cute_math.h>

#include "cute.h"

// Class/module definitions
static struct RClass *mCute;

// Initialize the module
void mrb_mruby_cute_gem_init(mrb_state *mrb)
{
  // Create Cute module
  mCute = mrb_define_module(mrb, "Cute");

  // Initialize submodules
  void mrb_mruby_cute_cute_app_gem_init(mrb_state *mrb, struct RClass *mCute);
  void mrb_mruby_cute_cute_color_gem_init(mrb_state *mrb, struct RClass *mCute);
  void mrb_mruby_cute_cute_math_gem_init(mrb_state *mrb, struct RClass *mCute);
}

// Cleanup
void mrb_mruby_cute_gem_final(mrb_state *mrb) {
  // Nothing to clean up
}
