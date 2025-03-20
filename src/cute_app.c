#include "cute.h"
#include <cute_app.h>

/**
 * Struct definitions
 */
static const struct mrb_data_type CF_PowerInfo_type = { "CF_PowerInfo", mrb_free };

/**
 * Data type definitions
 */
typedef struct mrb_cf_powerinfo_data_t {
  CF_PowerInfo* cf_powerinfo_ptr;
} mrb_cf_powerinfo_data_t;


/**
 * Function wrapper declarations TODO: Move to header
 */
static mrb_value mrb_cf_app_center_window(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_dpi_scale_was_changed(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_draw_onto_screen(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_gained_focus(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_canvas(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_canvas_height(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_canvas_width(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_dpi_scale(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_framerate(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_height(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_position(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_size(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_smoothed_framerate(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_vsync(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_get_width(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_has_focus(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_init_imgui(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_is_running(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_lost_focus(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_maximized(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_minimized(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_mouse_entered(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_mouse_exited(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_mouse_inside(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_power_info(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_request_attention(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_request_attention_cancel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_request_attention_continuously(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_borderless_fullscreen_mode(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_canvas_size(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_fullscreen_mode(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_icon(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_position(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_size(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_title(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_vsync(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_vsync_mailbox(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_set_windowed_mode(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_show_window(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_signal_shutdown(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_update(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_was_maximized(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_was_minimized(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_was_moved(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_was_resized(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_app_was_restored(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_default_display(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_destroy_app(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_bounds(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_count(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_height(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_orientation(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_refresh_rate(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_width(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_x(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_display_y(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_free_display_list(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_get_display_list(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_app(mrb_state *mrb, mrb_value self);

/**
 * Function wrappers
 */
/*  */
static mrb_value mrb_cf_app_center_window(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_center_window();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_dpi_scale_was_changed(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_dpi_scale_was_changed();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_draw_onto_screen(mrb_state *mrb, mrb_value self) {
  mrb_value clear;

  mrb_get_args(mrb, "o", &clear);

  bool c_clear = mrb_bool(clear);

  int result = cf_app_draw_onto_screen(c_clear);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_gained_focus(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_gained_focus();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_get_canvas(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Canvas result = cf_app_get_canvas();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_get_canvas_height(mrb_state *mrb, mrb_value self) {
  // No parameters
  int result = cf_app_get_canvas_height();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_get_canvas_width(mrb_state *mrb, mrb_value self) {
  // No parameters
  int result = cf_app_get_canvas_width();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_get_dpi_scale(mrb_state *mrb, mrb_value self) {
  // No parameters
  float result = cf_app_get_dpi_scale();
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_get_framerate(mrb_state *mrb, mrb_value self) {
  // No parameters
  float result = cf_app_get_framerate();
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_get_height(mrb_state *mrb, mrb_value self) {
  // No parameters
  int result = cf_app_get_height();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_get_position(mrb_state *mrb, mrb_value self) {
  mrb_value x, y;

  mrb_get_args(mrb, "oo", &x, &y);

  int* c_x = mrb_cptr(x);
  int* c_y = mrb_cptr(y);

  cf_app_get_position(c_x, c_y);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_get_size(mrb_state *mrb, mrb_value self) {
  mrb_value w, h;

  mrb_get_args(mrb, "oo", &w, &h);

  int* c_w = mrb_cptr(w);
  int* c_h = mrb_cptr(h);

  cf_app_get_size(c_w, c_h);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_get_smoothed_framerate(mrb_state *mrb, mrb_value self) {
  // No parameters
  float result = cf_app_get_smoothed_framerate();
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_get_vsync(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_get_vsync();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_get_width(mrb_state *mrb, mrb_value self) {
  // No parameters
  int result = cf_app_get_width();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_has_focus(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_has_focus();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_init_imgui(mrb_state *mrb, mrb_value self) {
  // No parameters
  ImGuiContext* result = cf_app_init_imgui();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_is_running(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_is_running();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_lost_focus(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_lost_focus();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_maximized(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_maximized();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_minimized(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_minimized();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_mouse_entered(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_mouse_entered();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_mouse_exited(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_mouse_exited();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_mouse_inside(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_mouse_inside();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_power_info(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_PowerInfo result = cf_app_power_info();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_app_request_attention(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_request_attention();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_request_attention_cancel(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_request_attention_cancel();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_request_attention_continuously(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_request_attention_continuously();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_borderless_fullscreen_mode(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_set_borderless_fullscreen_mode();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_canvas_size(mrb_state *mrb, mrb_value self) {
  mrb_value w, h;

  mrb_get_args(mrb, "oo", &w, &h);

  int c_w = mrb_fixnum(w);
  int c_h = mrb_fixnum(h);

  cf_app_set_canvas_size(c_w, c_h);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_fullscreen_mode(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_set_fullscreen_mode();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_icon(mrb_state *mrb, mrb_value self) {
  mrb_value virtual_path_to_png;

  mrb_get_args(mrb, "o", &virtual_path_to_png);

  const char* c_virtual_path_to_png = mrb_str_to_cstr(mrb, virtual_path_to_png);

  cf_app_set_icon(c_virtual_path_to_png);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_position(mrb_state *mrb, mrb_value self) {
  mrb_value x, y;

  mrb_get_args(mrb, "oo", &x, &y);

  int c_x = mrb_fixnum(x);
  int c_y = mrb_fixnum(y);

  cf_app_set_position(c_x, c_y);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_size(mrb_state *mrb, mrb_value self) {
  mrb_value w, h;

  mrb_get_args(mrb, "oo", &w, &h);

  int c_w = mrb_fixnum(w);
  int c_h = mrb_fixnum(h);

  cf_app_set_size(c_w, c_h);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_title(mrb_state *mrb, mrb_value self) {
  mrb_value title;

  mrb_get_args(mrb, "o", &title);

  const char* c_title = mrb_str_to_cstr(mrb, title);

  cf_app_set_title(c_title);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_vsync(mrb_state *mrb, mrb_value self) {
  mrb_value true_turn_on_vsync;

  mrb_get_args(mrb, "o", &true_turn_on_vsync);

  bool c_true_turn_on_vsync = mrb_bool(true_turn_on_vsync);

  cf_app_set_vsync(c_true_turn_on_vsync);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_vsync_mailbox(mrb_state *mrb, mrb_value self) {
  mrb_value true_turn_on_mailbox;

  mrb_get_args(mrb, "o", &true_turn_on_mailbox);

  bool c_true_turn_on_mailbox = mrb_bool(true_turn_on_mailbox);

  cf_app_set_vsync_mailbox(c_true_turn_on_mailbox);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_set_windowed_mode(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_set_windowed_mode();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_show_window(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_show_window();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_signal_shutdown(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_app_signal_shutdown();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_update(mrb_state *mrb, mrb_value self) {
  mrb_value on_update;

  mrb_get_args(mrb, "o", &on_update);

  CF_OnUpdateFn* c_on_update = mrb_cptr(on_update);

  cf_app_update(c_on_update);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_app_was_maximized(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_was_maximized();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_was_minimized(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_was_minimized();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_was_moved(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_was_moved();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_was_resized(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_was_resized();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_app_was_restored(mrb_state *mrb, mrb_value self) {
  // No parameters
  bool result = cf_app_was_restored();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_default_display(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_DisplayID result = cf_default_display();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_destroy_app(mrb_state *mrb, mrb_value self) {
  // No parameters
  cf_destroy_app();
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_display_bounds(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  CF_Rect result = cf_display_bounds(c_display_id);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_display_count(mrb_state *mrb, mrb_value self) {
  // No parameters
  int result = cf_display_count();
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_display_height(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  int result = cf_display_height(c_display_id);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_display_orientation(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  CF_DisplayOrientation result = cf_display_orientation(c_display_id);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_display_refresh_rate(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  float result = cf_display_refresh_rate(c_display_id);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_display_width(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  int result = cf_display_width(c_display_id);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_display_x(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  int result = cf_display_x(c_display_id);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_display_y(mrb_state *mrb, mrb_value self) {
  mrb_value display_id;

  mrb_get_args(mrb, "o", &display_id);

  CF_DisplayID c_display_id = mrb_fixnum(display_id);

  int result = cf_display_y(c_display_id);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_free_display_list(mrb_state *mrb, mrb_value self) {
  mrb_value display_list;

  mrb_get_args(mrb, "o", &display_list);

  CF_DisplayID* c_display_list = mrb_cptr(display_list);

  cf_free_display_list(c_display_list);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_get_display_list(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_DisplayID* result = cf_get_display_list();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_app(mrb_state *mrb, mrb_value self) {
  mrb_value window_title, display_id, x, y, w, h, options, argv0;

  mrb_get_args(mrb, "oooooooo", &window_title, &display_id, &x, &y, &w, &h, &options, &argv0);

  const char* c_window_title = mrb_str_to_cstr(mrb, window_title);
  CF_DisplayID c_display_id = mrb_fixnum(display_id);
  int c_x = mrb_fixnum(x);
  int c_y = mrb_fixnum(y);
  int c_w = mrb_fixnum(w);
  int c_h = mrb_fixnum(h);
  CF_AppOptionFlags c_options = mrb_fixnum(options);
  const char* c_argv0 = mrb_str_to_cstr(mrb, argv0);

  CF_Result result = cf_make_app(c_window_title, c_display_id, c_x, c_y, c_w, c_h, c_options, c_argv0);
  return mrb_cptr_value(mrb, result);
}
CF_PowerInfo* mrb_cf_powerinfo_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_powerinfo_data_t* data = (mrb_cf_powerinfo_data_t*) DATA_PTR(self);
    return data->cf_powerinfo_ptr;
}


/**
 * Initialize the module
 */
void mrb_mruby_cute_cute_app_gem_init(mrb_state *mrb, struct RClass *mCute)
{
  // Define enums
  

  // Define enum def definitions
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
  CF_DISPLAY_ORIENTATION_DEFS
  #undef CF_ENUM
  
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
  CF_APP_OPTION_DEFS
  #undef CF_ENUM
  
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
  CF_POWER_STATE_DEFS
  #undef CF_ENUM

  // Define functions
  mrb_define_module_function(mrb, mCute, "cf_app_center_window", mrb_cf_app_center_window, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_dpi_scale_was_changed", mrb_cf_app_dpi_scale_was_changed, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_draw_onto_screen", mrb_cf_app_draw_onto_screen, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_gained_focus", mrb_cf_app_gained_focus, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_canvas", mrb_cf_app_get_canvas, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_canvas_height", mrb_cf_app_get_canvas_height, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_canvas_width", mrb_cf_app_get_canvas_width, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_dpi_scale", mrb_cf_app_get_dpi_scale, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_framerate", mrb_cf_app_get_framerate, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_height", mrb_cf_app_get_height, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_position", mrb_cf_app_get_position, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_app_get_size", mrb_cf_app_get_size, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_app_get_smoothed_framerate", mrb_cf_app_get_smoothed_framerate, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_vsync", mrb_cf_app_get_vsync, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_get_width", mrb_cf_app_get_width, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_has_focus", mrb_cf_app_has_focus, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_init_imgui", mrb_cf_app_init_imgui, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_is_running", mrb_cf_app_is_running, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_lost_focus", mrb_cf_app_lost_focus, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_maximized", mrb_cf_app_maximized, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_minimized", mrb_cf_app_minimized, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_mouse_entered", mrb_cf_app_mouse_entered, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_mouse_exited", mrb_cf_app_mouse_exited, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_mouse_inside", mrb_cf_app_mouse_inside, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_power_info", mrb_cf_app_power_info, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_request_attention", mrb_cf_app_request_attention, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_request_attention_cancel", mrb_cf_app_request_attention_cancel, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_request_attention_continuously", mrb_cf_app_request_attention_continuously, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_set_borderless_fullscreen_mode", mrb_cf_app_set_borderless_fullscreen_mode, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_set_canvas_size", mrb_cf_app_set_canvas_size, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_app_set_fullscreen_mode", mrb_cf_app_set_fullscreen_mode, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_set_icon", mrb_cf_app_set_icon, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_set_position", mrb_cf_app_set_position, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_app_set_size", mrb_cf_app_set_size, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_app_set_title", mrb_cf_app_set_title, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_set_vsync", mrb_cf_app_set_vsync, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_set_vsync_mailbox", mrb_cf_app_set_vsync_mailbox, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_set_windowed_mode", mrb_cf_app_set_windowed_mode, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_show_window", mrb_cf_app_show_window, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_signal_shutdown", mrb_cf_app_signal_shutdown, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_update", mrb_cf_app_update, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_app_was_maximized", mrb_cf_app_was_maximized, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_was_minimized", mrb_cf_app_was_minimized, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_was_moved", mrb_cf_app_was_moved, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_was_resized", mrb_cf_app_was_resized, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_app_was_restored", mrb_cf_app_was_restored, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_default_display", mrb_cf_default_display, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_destroy_app", mrb_cf_destroy_app, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_display_bounds", mrb_cf_display_bounds, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_count", mrb_cf_display_count, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_display_height", mrb_cf_display_height, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_orientation", mrb_cf_display_orientation, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_refresh_rate", mrb_cf_display_refresh_rate, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_width", mrb_cf_display_width, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_x", mrb_cf_display_x, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_display_y", mrb_cf_display_y, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_free_display_list", mrb_cf_free_display_list, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_get_display_list", mrb_cf_get_display_list, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_make_app", mrb_cf_make_app, MRB_ARGS_REQ(8));
}
