#include "text.h"
#include "vector.h"
#include "result.h"

static mrb_value mrb_cf_make_font(mrb_state* mrb, mrb_value self)
{
    char* path;
    char* font_name;

    mrb_get_args(mrb, "zz", &path, &font_name);

    CF_Result result = cf_make_font(path, font_name);

    return mrb_cf_result_from_cf_result(mrb, result);
}

static mrb_value mrb_cf_push_font(mrb_state* mrb, mrb_value self)
{
    char* font_name;

    mrb_get_args(mrb, "z", &font_name);

    cf_push_font(font_name);

    return mrb_nil_value();
}

static mrb_value mrb_cf_pop_font(mrb_state* mrb, mrb_value self)
{
    cf_pop_font();
    return mrb_nil_value();
}

static mrb_value mrb_cf_push_font_size(mrb_state* mrb, mrb_value self)
{
    mrb_float size;

    mrb_get_args(mrb, "f", &size);

    cf_push_font_size((float)size);

    return mrb_nil_value();
}

static mrb_value mrb_cf_pop_font_size(mrb_state* mrb, mrb_value self)
{
    cf_pop_font_size();
    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_text(mrb_state* mrb, mrb_value self)
{
    mrb_value position_obj;
    char* text;
    mrb_int num_chars_to_draw = -1;

    mrb_get_args(mrb, "zo|i", &text, &position_obj, &num_chars_to_draw);

    CF_V2* position = mrb_cf_v2_unwrap(mrb, position_obj);

    cf_draw_text(text, *position, (int)num_chars_to_draw);

    return mrb_nil_value();
}

static mrb_value mrb_cf_text_width(mrb_state* mrb, mrb_value self)
{
    char* text;
    mrb_int num_chars_to_draw = -1;

    mrb_get_args(mrb, "z|i", &text, &num_chars_to_draw);

    float width = cf_text_width(text, (int)num_chars_to_draw);

    return mrb_float_value(mrb, width);
}

static mrb_value mrb_cf_text_height(mrb_state* mrb, mrb_value self)
{
    char* text;
    mrb_int num_chars_to_draw = -1;

    mrb_get_args(mrb, "z|i", &text, &num_chars_to_draw);

    float height = cf_text_height(text, (int)num_chars_to_draw);

    return mrb_float_value(mrb, height);
}

static mrb_value mrb_cf_text_size(mrb_state* mrb, mrb_value self)
{
    char* text;
    mrb_int num_chars_to_draw = -1;

    mrb_get_args(mrb, "z|i", &text, &num_chars_to_draw);

    CF_V2 size = cf_text_size(text, (int)num_chars_to_draw);

    return mrb_cf_v2_wrap_nested(mrb, &size);
}

void mrb_cute_text_init(mrb_state* mrb, struct RClass* mCute)
{
    // Font functions
    mrb_define_module_function(mrb, mCute, "cf_make_font", mrb_cf_make_font, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_push_font", mrb_cf_push_font, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pop_font", mrb_cf_pop_font, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_push_font_size", mrb_cf_push_font_size, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pop_font_size", mrb_cf_pop_font_size, MRB_ARGS_NONE());

    // Text functions
    mrb_define_module_function(mrb, mCute, "cf_draw_text", mrb_cf_draw_text, MRB_ARGS_ARG(2, 1));
    mrb_define_module_function(mrb, mCute, "cf_text_width", mrb_cf_text_width, MRB_ARGS_ARG(1, 1));
    mrb_define_module_function(mrb, mCute, "cf_text_height", mrb_cf_text_height, MRB_ARGS_ARG(1, 1));
    mrb_define_module_function(mrb, mCute, "cf_text_size", mrb_cf_text_size, MRB_ARGS_ARG(1, 1));
}