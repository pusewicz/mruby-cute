#include "aabb.h"
#include "circle.h"
#include "draw.h"
#include "result.h"
#include "vector.h"
#include <mruby/data.h>

static mrb_value mrb_cf_draw_sprite(mrb_state* mrb, mrb_value self)
{
    mrb_value sprite;
    CF_Sprite* s;

    mrb_get_args(mrb, "o", &sprite);
    s = DATA_PTR(sprite);

    cf_draw_sprite(s);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_push(mrb_state* mrb, mrb_value self)
{
    cf_draw_push();
    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_pop(mrb_state* mrb, mrb_value self)
{
    cf_draw_pop();
    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_scale(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y;

    mrb_get_args(mrb, "ff", &x, &y);
    cf_draw_scale(x, y);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_scale_v2(mrb_state* mrb, mrb_value self)
{
    mrb_value obj;

    mrb_get_args(mrb, "o", &obj);

    cf_draw_scale_v2(*mrb_cf_v2_unwrap(mrb, obj));

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_translate(mrb_state* mrb, mrb_value self)
{
    mrb_float x, y;

    mrb_get_args(mrb, "ff", &x, &y);
    cf_draw_translate((float)x, (float)y);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_translate_v2(mrb_state* mrb, mrb_value self)
{
    mrb_value obj;

    mrb_get_args(mrb, "o", &obj);

    cf_draw_translate_v2(*mrb_cf_v2_unwrap(mrb, obj));

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_rotate(mrb_state* mrb, mrb_value self)
{
    mrb_float radians;

    mrb_get_args(mrb, "f", &radians);
    cf_draw_rotate((float)radians);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_line(mrb_state* mrb, mrb_value self)
{
    mrb_value p0_obj, p1_obj;
    mrb_float thickness;

    mrb_get_args(mrb, "oof", &p0_obj, &p1_obj, &thickness);

    CF_V2* p0 = mrb_cf_v2_unwrap(mrb, p0_obj);
    CF_V2* p1 = mrb_cf_v2_unwrap(mrb, p1_obj);

    cf_draw_line(*p0, *p1, (float)thickness);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_quad(mrb_state* mrb, mrb_value self)
{
    mrb_value bb_obj;
    mrb_float thickness, chubbiness;

    mrb_get_args(mrb, "off", &bb_obj, &thickness, &chubbiness);

    CF_Aabb* bb = mrb_cf_aabb_unwrap(mrb, bb_obj);

    cf_draw_quad(*bb, (float)thickness, (float)chubbiness);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_quad2(mrb_state* mrb, mrb_value self)
{
    mrb_value p0_obj, p1_obj, p2_obj, p3_obj;
    mrb_float thickness, chubbiness;

    mrb_get_args(mrb, "ooooff", &p0_obj, &p1_obj, &p2_obj, &p3_obj, &thickness, &chubbiness);

    CF_V2* p0 = mrb_cf_v2_unwrap(mrb, p0_obj);
    CF_V2* p1 = mrb_cf_v2_unwrap(mrb, p1_obj);
    CF_V2* p2 = mrb_cf_v2_unwrap(mrb, p2_obj);
    CF_V2* p3 = mrb_cf_v2_unwrap(mrb, p3_obj);

    cf_draw_quad2(*p0, *p1, *p2, *p3, (float)thickness, (float)chubbiness);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_circle(mrb_state* mrb, mrb_value self)
{
    mrb_value circle_obj;
    mrb_float thickness;

    mrb_get_args(mrb, "of", &circle_obj, &thickness);

    CF_Circle* circle = mrb_cf_circle_unwrap(mrb, circle_obj);

    cf_draw_circle(*circle, (float)thickness);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_circle2(mrb_state* mrb, mrb_value self)
{
    mrb_value position_obj;
    mrb_float radius, thickness;

    mrb_get_args(mrb, "off", &position_obj, &radius, &thickness);

    CF_V2* position = mrb_cf_v2_unwrap(mrb, position_obj);

    cf_draw_circle2(*position, (float)radius, (float)thickness);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_circle_fill(mrb_state* mrb, mrb_value self)
{
    mrb_value circle_obj;

    mrb_get_args(mrb, "o", &circle_obj);

    CF_Circle* circle = mrb_cf_circle_unwrap(mrb, circle_obj);

    cf_draw_circle_fill(*circle);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_circle_fill2(mrb_state* mrb, mrb_value self)
{
    mrb_value position_obj;
    mrb_float radius;

    mrb_get_args(mrb, "of", &position_obj, &radius);

    CF_V2* position = mrb_cf_v2_unwrap(mrb, position_obj);

    cf_draw_circle_fill2(*position, (float)radius);

    return mrb_nil_value();
}

static mrb_value mrb_cf_draw_text(mrb_state* mrb, mrb_value self)
{
    mrb_value position_obj;
    char* text;
    mrb_int num_chars_to_draw = -1;

    mrb_get_args(mrb, "zo|i", &text, &position_obj, &num_chars_to_draw);

    CF_V2 position = *mrb_cf_v2_unwrap(mrb, position_obj);

    cf_draw_text(text, position, (int)num_chars_to_draw);

    return mrb_nil_value();
}

static mrb_value mrb_cf_make_font(mrb_state* mrb, mrb_value self)
{
    char* path;
    char* font_name;

    mrb_get_args(mrb, "zz", &path, &font_name);

    CF_Result result = cf_make_font(path, font_name);

    return mrb_cf_result_wrap_nested(mrb, &result);
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

void mrb_cute_draw_init(mrb_state* mrb, struct RClass* mCute)
{
    mrb_define_module_function(mrb, mCute, "cf_draw_sprite", mrb_cf_draw_sprite, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_scale", mrb_cf_draw_scale, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_draw_scale_v2", mrb_cf_draw_scale_v2, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_translate", mrb_cf_draw_translate, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_draw_translate_v2", mrb_cf_draw_translate_v2, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_rotate", mrb_cf_draw_rotate, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_push", mrb_cf_draw_push, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_draw_pop", mrb_cf_draw_pop, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_draw_line", mrb_cf_draw_line, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "cf_draw_quad", mrb_cf_draw_quad, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "cf_draw_quad2", mrb_cf_draw_quad2, MRB_ARGS_REQ(6));
    mrb_define_module_function(mrb, mCute, "cf_draw_circle", mrb_cf_draw_circle, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_draw_circle2", mrb_cf_draw_circle2, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "cf_draw_circle_fill", mrb_cf_draw_circle_fill, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_circle_fill2", mrb_cf_draw_circle_fill2, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_draw_text", mrb_cf_draw_text, MRB_ARGS_ARG(2, 1));

    // Font functions
    mrb_define_module_function(mrb, mCute, "cf_make_font", mrb_cf_make_font, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_push_font", mrb_cf_push_font, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pop_font", mrb_cf_pop_font, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_push_font_size", mrb_cf_push_font_size, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pop_font_size", mrb_cf_pop_font_size, MRB_ARGS_NONE());

    // Text measurement functions
    mrb_define_module_function(mrb, mCute, "cf_text_width", mrb_cf_text_width, MRB_ARGS_ARG(1, 1));
    mrb_define_module_function(mrb, mCute, "cf_text_height", mrb_cf_text_height, MRB_ARGS_ARG(1, 1));
    mrb_define_module_function(mrb, mCute, "cf_text_size", mrb_cf_text_size, MRB_ARGS_ARG(1, 1));
}
