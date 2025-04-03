#include "draw.h"
#include "sprite.h"
#include "vector.h"

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

void mrb_cute_draw_init(mrb_state* mrb, struct RClass* mCute)
{
    mrb_define_module_function(mrb, mCute, "cf_draw_sprite", mrb_cf_draw_sprite, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_scale", mrb_cf_draw_scale, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_draw_scale_v2", mrb_cf_draw_scale_v2, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_rotate", mrb_cf_draw_rotate, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_draw_push", mrb_cf_draw_push, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_draw_pop", mrb_cf_draw_pop, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_draw_line", mrb_cf_draw_line, MRB_ARGS_REQ(3));
}
