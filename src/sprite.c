#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>

static const struct mrb_data_type mrb_cf_sprite_type = {"CF_Sprite", mrb_free};

/*
 * CF_Sprite
 */

static mrb_value mrb_cf_sprite_initialize(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = (CF_Sprite*) DATA_PTR(self);
  if (sprite) mrb_free(mrb, sprite);
  DATA_TYPE(self) = &mrb_cf_sprite_type;
  DATA_PTR(self) = mrb_malloc(mrb, sizeof(CF_Sprite));
  return self;
}

/*
 * cute_sprite
 */

static mrb_value mrb_cf_make_demo_sprite(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite_ptr = (CF_Sprite*) mrb_malloc(mrb, sizeof(CF_Sprite));
  *sprite_ptr = cf_make_demo_sprite();
  struct RClass* cf_sprite_class = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_Sprite");
  return mrb_obj_value(Data_Wrap_Struct(mrb, cf_sprite_class, &mrb_cf_sprite_type, sprite_ptr));
}

static mrb_value mrb_cf_sprite_defaults(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite_ptr = (CF_Sprite*) mrb_malloc(mrb, sizeof(CF_Sprite));
  *sprite_ptr = cf_sprite_defaults();
  struct RClass* cf_sprite_class = mrb_class_get_under(mrb, mrb_module_get(mrb, "Cute"), "CF_Sprite");
  return mrb_obj_value(Data_Wrap_Struct(mrb, cf_sprite_class, &mrb_cf_sprite_type, sprite_ptr));
}

static mrb_value mrb_cf_sprite_draw(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  cf_sprite_draw(sprite);
  return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_height(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  return mrb_fixnum_value(cf_sprite_height(sprite));
}

static mrb_value mrb_cf_sprite_is_playing(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  char* animation;
  mrb_get_args(mrb, "dz", &sprite, &mrb_cf_sprite_type, &animation);
  return mrb_bool_value(cf_sprite_is_playing(sprite, animation));
}

static mrb_value mrb_cf_sprite_play(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  char* animation;
  mrb_get_args(mrb, "dz", &sprite, &mrb_cf_sprite_type, &animation);
  cf_sprite_play(sprite, animation);
  return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_update(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  cf_sprite_update(sprite);
  return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_width(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  return mrb_fixnum_value(cf_sprite_width(sprite));
}

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* cute_module)
{
  // CF_Sprite
  struct RClass* cf_sprite_class = mrb_define_class_under(mrb, cute_module, "CF_Sprite", mrb->object_class);
  MRB_SET_INSTANCE_TT(cf_sprite_class, MRB_TT_DATA);

  mrb_define_method(mrb, cf_sprite_class, "initialize", mrb_cf_sprite_initialize, MRB_ARGS_NONE());

  // cute_sprite
  mrb_define_module_function(mrb, cute_module, "cf_make_demo_sprite", mrb_cf_make_demo_sprite, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, cute_module, "cf_sprite_defaults", mrb_cf_sprite_defaults, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, cute_module, "cf_sprite_draw", mrb_cf_sprite_draw, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cute_module, "cf_sprite_height", mrb_cf_sprite_height, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cute_module, "cf_sprite_is_playing", mrb_cf_sprite_is_playing, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, cute_module, "cf_sprite_play", mrb_cf_sprite_play, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, cute_module, "cf_sprite_update", mrb_cf_sprite_update, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, cute_module, "cf_sprite_width", mrb_cf_sprite_width, MRB_ARGS_REQ(1));
}
