#include "app.h"
#include "result.h"

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

    CF_Result* result = (CF_Result*)mrb_malloc(mrb, sizeof(CF_Result));
    *result = cf_make_app(window_title, display_id, x, y, w, h, options, argv0);

    return mrb_cf_result_wrap(mrb, result);
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

typedef struct mrb_cf_callback_data {
    mrb_state* mrb;
    mrb_value callback;
} mrb_cf_callback_data;

void mrb_cf_app_update_callback_function(void* ptr)
{
    mrb_cf_callback_data* data = (mrb_cf_callback_data*)ptr;
    mrb_state* mrb = data->mrb;
    mrb_value callback = data->callback;

    // Call the Ruby callback
    mrb_funcall(mrb, callback, "call", 0);
}

static mrb_value mrb_cf_app_update(mrb_state* mrb, mrb_value self)
{
    mrb_value on_update_callback = mrb_nil_value();

    mrb_get_args(mrb, "|&", &on_update_callback);

    if (mrb_nil_p(on_update_callback)) {
        // No callback provided, use the default update function
        cf_app_update(NULL);
    } else {
        // Wrap the callback in a struct to pass it to the C function
        mrb_cf_callback_data data;

        data.mrb = mrb;
        data.callback = on_update_callback;

        cf_set_update_udata(&data);
        cf_app_update(mrb_cf_app_update_callback_function);
    }

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

// cf_app_get_framerate
static mrb_value mrb_cf_app_get_framerate(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, cf_app_get_framerate());
}

// cf_app_get_smoothed_framerate
static mrb_value mrb_cf_app_get_smoothed_framerate(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, cf_app_get_smoothed_framerate());
}

// cf_app_set_title
static mrb_value mrb_cf_app_set_title(mrb_state* mrb, mrb_value self)
{
    char* title;
    mrb_get_args(mrb, "z", &title);
    cf_app_set_title(title);
    return mrb_nil_value();
}

// cf_app_get_vsync
static mrb_value mrb_cf_app_get_vsync(mrb_state* mrb, mrb_value self)
{
    return mrb_bool_value(cf_app_get_vsync());
}

// cf_app_set_vsync
static mrb_value mrb_cf_app_set_vsync(mrb_state* mrb, mrb_value self)
{
    mrb_bool vsync;
    mrb_get_args(mrb, "b", &vsync);
    cf_app_set_vsync(vsync);
    return mrb_nil_value();
}

// cf_app_get_dpi_scale
static mrb_value mrb_cf_app_get_dpi_scale(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, cf_app_get_dpi_scale());
}

// cf_app_get_width
static mrb_value mrb_cf_app_get_width(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(cf_app_get_width());
}

// cf_app_get_height
static mrb_value mrb_cf_app_get_height(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(cf_app_get_height());
}

void mrb_cute_app_init(mrb_state* mrb, struct RClass* mCute)
{
#define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_" #K, mrb_fixnum_value(V));
    CF_APP_OPTION_DEFS
#undef CF_ENUM
    mrb_define_module_function(mrb, mCute, "cf_make_app", mrb_cf_make_app, MRB_ARGS_REQ(7));
    mrb_define_module_function(mrb, mCute, "cf_app_is_running", mrb_cf_app_is_running, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_destroy", mrb_cf_app_destroy, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_update", mrb_cf_app_update, MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mCute, "cf_default_display", mrb_cf_default_display, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_draw_onto_screen", mrb_cf_app_draw_onto_screen, MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mCute, "cf_app_get_framerate", mrb_cf_app_get_framerate, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_get_smoothed_framerate", mrb_cf_app_get_smoothed_framerate, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_set_title", mrb_cf_app_set_title, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_app_get_vsync", mrb_cf_app_get_vsync, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_set_vsync", mrb_cf_app_set_vsync, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_app_get_dpi_scale", mrb_cf_app_get_dpi_scale, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_get_width", mrb_cf_app_get_width, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_app_get_height", mrb_cf_app_get_height, MRB_ARGS_NONE());
}
