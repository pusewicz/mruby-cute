#include "sprite.h"
#include "transform.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>
#include <mruby/variable.h>

static struct RClass* cSprite;

static void mrb_cf_sprite_free(mrb_state* mrb, void* p)
{
    CF_Sprite* sprite = (CF_Sprite*)p;
    mrb_free(mrb, sprite);
}

static const struct mrb_data_type mrb_cf_sprite_type = {
    "CF_Sprite", mrb_cf_sprite_free
};

static mrb_value mrb_cf_sprite_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = (CF_Sprite*)mrb_malloc(mrb, sizeof(CF_Sprite));

    *sprite = cf_sprite_defaults();

    DATA_PTR(self) = sprite;
    DATA_TYPE(self) = &mrb_cf_sprite_type;

    return self;
}

static mrb_value mrb_cf_sprite_wrap(mrb_state* mrb, CF_Sprite* sprite)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cSprite, &mrb_cf_sprite_type, sprite));
}

static mrb_value mrb_cf_sprite_name(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_str_new_cstr(mrb, sprite->name);
}

static mrb_value mrb_cf_sprite_get_w(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_fixnum_value(cf_sprite_width(sprite));
}

static mrb_value mrb_cf_sprite_get_h(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_fixnum_value(cf_sprite_height(sprite));
}

static mrb_value mrb_cf_sprite_get_opacity(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_float_value(mrb, cf_sprite_get_opacity(sprite));
}

static mrb_value mrb_cf_sprite_set_opacity(mrb_state* mrb, mrb_value self)
{
    mrb_float opacity;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "f", &opacity);

    cf_sprite_set_opacity(sprite, opacity);

    return mrb_float_value(mrb, opacity);
}

static mrb_value mrb_cf_sprite_get_scale_x(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_float_value(mrb, cf_sprite_get_scale_x(sprite));
}

static mrb_value mrb_cf_sprite_set_scale_x(mrb_state* mrb, mrb_value self)
{
    mrb_float scale_x;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "f", &scale_x);

    cf_sprite_set_scale_x(sprite, scale_x);

    return mrb_float_value(mrb, scale_x);
}

static mrb_value mrb_cf_sprite_get_scale_y(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_float_value(mrb, cf_sprite_get_scale_y(sprite));
}

static mrb_value mrb_cf_sprite_set_scale_y(mrb_state* mrb, mrb_value self)
{
    mrb_float scale_y;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "f", &scale_y);

    cf_sprite_set_scale_y(sprite, scale_y);

    return mrb_float_value(mrb, scale_y);
}

static mrb_value mrb_cf_sprite_get_offset_x(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_float_value(mrb, cf_sprite_get_offset_x(sprite));
}

static mrb_value mrb_cf_sprite_get_offset_y(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_float_value(mrb, cf_sprite_get_offset_y(sprite));
}

static mrb_value mrb_cf_sprite_set_offset_x(mrb_state* mrb, mrb_value self)
{
    mrb_float offset_x;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "f", &offset_x);

    cf_sprite_set_offset_x(sprite, offset_x);

    return mrb_float_value(mrb, offset_x);
}

static mrb_value mrb_cf_sprite_set_offset_y(mrb_state* mrb, mrb_value self)
{
    mrb_float offset_y;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "f", &offset_y);

    cf_sprite_set_offset_y(sprite, offset_y);

    return mrb_float_value(mrb, offset_y);
}

static mrb_value mrb_cf_make_demo_sprite(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = (CF_Sprite*)mrb_malloc(mrb, sizeof(CF_Sprite));

    *sprite = cf_make_demo_sprite();

    return mrb_cf_sprite_wrap(mrb, sprite);
}

static mrb_value mrb_cf_sprite_defaults(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = (CF_Sprite*)mrb_malloc(mrb, sizeof(CF_Sprite));

    *sprite = cf_sprite_defaults();

    return mrb_cf_sprite_wrap(mrb, sprite);
}

static mrb_value mrb_cf_sprite_draw(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_draw(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_is_playing(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);
    char* animation;

    mrb_get_args(mrb, "z", &animation);

    return mrb_bool_value(cf_sprite_is_playing(sprite, animation));
}

static mrb_value mrb_cf_sprite_pause(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_pause(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_unpause(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_unpause(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_toggle_pause(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_toggle_pause(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_play(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);
    char* animation;

    mrb_get_args(mrb, "z", &animation);

    cf_sprite_play(sprite, animation);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_update(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_update(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_reload(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    *sprite = cf_sprite_reload(sprite);

    return self;
}

static mrb_value mrb_cf_sprite_reset(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_reset(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_get_loop(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_bool_value(cf_sprite_get_loop(sprite));
}

static mrb_value mrb_cf_sprite_set_loop(mrb_state* mrb, mrb_value self)
{
    mrb_bool loop;
    CF_Sprite* sprite = DATA_PTR(self);

    mrb_get_args(mrb, "b", &loop);

    cf_sprite_set_loop(sprite, loop);

    return mrb_bool_value(loop);
}

static mrb_value mrb_cf_sprite_flip_x(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_flip_x(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_flip_y(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    cf_sprite_flip_y(sprite);

    return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_frame_count(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_fixnum_value(cf_sprite_frame_count(sprite));
}

static mrb_value mrb_cf_sprite_current_frame(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    return mrb_fixnum_value(cf_sprite_current_frame(sprite));
}

static mrb_value mrb_cf_sprite_get_transform(mrb_state* mrb, mrb_value self)
{
    CF_Sprite* sprite = DATA_PTR(self);

    // Check if the transform is already set
    mrb_sym iv_name = mrb_intern_lit(mrb, "transform");
    mrb_value transform_obj = mrb_iv_get(mrb, self, iv_name);
    if (!mrb_nil_p(transform_obj)) {
        return transform_obj;
    }

    // Create a new transform object
    transform_obj = mrb_cf_transform_wrap_contained(mrb, &sprite->transform);
    mrb_iv_set(mrb, self, iv_name, transform_obj);
    mrb_iv_set(mrb, transform_obj, mrb_intern_lit(mrb, "sprite"), self);

    return transform_obj;
}

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mCute)
{
    // Create Sprite class
    cSprite = mrb_define_class_under_id(mrb, mCute, MRB_SYM(Sprite), mrb->object_class);
    MRB_SET_INSTANCE_TT(cSprite, MRB_TT_CDATA);

    mrb_define_method_id(mrb, cSprite, MRB_SYM(initialize), mrb_cf_sprite_initialize, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(name), mrb_cf_sprite_name, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(w), mrb_cf_sprite_get_w, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(h), mrb_cf_sprite_get_h, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(scale_x), mrb_cf_sprite_get_scale_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(scale_x), mrb_cf_sprite_set_scale_x, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(scale_y), mrb_cf_sprite_get_scale_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(scale_y), mrb_cf_sprite_set_scale_y, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(opacity), mrb_cf_sprite_get_opacity, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(opacity), mrb_cf_sprite_set_opacity, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(draw), mrb_cf_sprite_draw, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(update), mrb_cf_sprite_update, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(play), mrb_cf_sprite_play, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM_Q(playing), mrb_cf_sprite_is_playing, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(pause), mrb_cf_sprite_pause, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(unpause), mrb_cf_sprite_unpause, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_B(toggle_pause), mrb_cf_sprite_toggle_pause, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(reload), mrb_cf_sprite_reload, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(reset), mrb_cf_sprite_reset, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_Q(loop), mrb_cf_sprite_get_loop, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(loop), mrb_cf_sprite_set_loop, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(scale_x), mrb_cf_sprite_get_scale_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(scale_y), mrb_cf_sprite_get_scale_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(scale_x), mrb_cf_sprite_set_scale_x, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(scale_y), mrb_cf_sprite_set_scale_y, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM(offset_x), mrb_cf_sprite_get_offset_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(offset_y), mrb_cf_sprite_get_offset_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(offset_x), mrb_cf_sprite_set_offset_x, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM_E(offset_y), mrb_cf_sprite_set_offset_y, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSprite, MRB_SYM_B(flip_x), mrb_cf_sprite_flip_x, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM_B(flip_y), mrb_cf_sprite_flip_y, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(frame_count), mrb_cf_sprite_frame_count, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(current_frame), mrb_cf_sprite_current_frame, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSprite, MRB_SYM(transform), mrb_cf_sprite_get_transform, MRB_ARGS_NONE());

    // cute_sprite
    mrb_define_module_function_id(mrb, mCute, MRB_SYM(cf_make_demo_sprite), mrb_cf_make_demo_sprite, MRB_ARGS_NONE());
    mrb_define_module_function_id(mrb, mCute, MRB_SYM(cf_sprite_defaults), mrb_cf_sprite_defaults, MRB_ARGS_NONE());
}
