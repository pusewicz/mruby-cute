#include "mrb_cute.h"

// cf_key_down
static mrb_value mrb_cf_key_down(mrb_state* mrb, mrb_value self)
{
  int key;
  mrb_get_args(mrb, "i", &key);
  return mrb_bool_value(cf_key_down(key));
}

// cf_key_up
static mrb_value mrb_cf_key_up(mrb_state* mrb, mrb_value self)
{
  int key;
  mrb_get_args(mrb, "i", &key);
  return mrb_bool_value(cf_key_up(key));
}

// cf_key_just_pressed
static mrb_value mrb_cf_key_just_pressed(mrb_state* mrb, mrb_value self)
{
  int key;
  mrb_get_args(mrb, "i", &key);
  return mrb_bool_value(cf_key_just_pressed(key));
}

// cf_key_just_released
static mrb_value mrb_cf_key_just_released(mrb_state* mrb, mrb_value self)
{
  int key;
  mrb_get_args(mrb, "i", &key);
  return mrb_bool_value(cf_key_just_released(key));
}

// cf_key_repeating
static mrb_value mrb_cf_key_repeating(mrb_state* mrb, mrb_value self)
{
  int key;
  mrb_get_args(mrb, "i", &key);
  return mrb_bool_value(cf_key_repeating(key));
}

// cf_key_ctrl
static mrb_value mrb_cf_key_ctrl(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_key_ctrl());
}

// cf_key_shift
static mrb_value mrb_cf_key_shift(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_key_shift());
}

// cf_key_alt
static mrb_value mrb_cf_key_alt(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_key_alt());
}

// cf_key_gui
static mrb_value mrb_cf_key_gui(mrb_state* mrb, mrb_value self)
{
  return mrb_bool_value(cf_key_gui());
}

// cf_clear_key_states
static mrb_value mrb_cf_clear_key_states(mrb_state* mrb, mrb_value self)
{
  cf_clear_key_states();
  return mrb_nil_value();
}

void mrb_cute_input_init(mrb_state* mrb, struct RClass* mCute)
{
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
  CF_KEY_BUTTON_DEFS
  #undef CF_ENUM

  mrb_define_module_function(mrb, mCute, "cf_key_down", mrb_cf_key_down, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_key_up", mrb_cf_key_up, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_key_just_pressed", mrb_cf_key_just_pressed, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_key_just_released", mrb_cf_key_just_released, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_key_repeating", mrb_cf_key_repeating, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_key_ctrl", mrb_cf_key_ctrl, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_key_shift", mrb_cf_key_shift, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_key_alt", mrb_cf_key_alt, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_key_gui", mrb_cf_key_gui, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mCute, "cf_clear_key_states", mrb_cf_clear_key_states, MRB_ARGS_NONE());
}
