#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/string.h>

static void mrb_sprite_free(mrb_state* mrb, void* p)
{
  if (p) {
    mrb_free(mrb, p);
  }
}

static const struct mrb_data_type mrb_sprite_type = {"Sprite", mrb_sprite_free};

static mrb_value mrb_sprite_make_sprite(mrb_state* mrb, mrb_value self)
{
  char* aseprite_path;
  mrb_get_args(mrb, "z", &aseprite_path);

  CF_Sprite* sprite = (CF_Sprite*) mrb_malloc(mrb, sizeof(CF_Sprite));
  *sprite = cf_make_sprite(aseprite_path);

  struct RClass* cute_module = mrb_module_get(mrb, "Cute");
  struct RData* data = mrb_data_object_alloc(mrb, mrb_class_get_under(mrb, cute_module, "Sprite"), sprite, &mrb_sprite_type);
  return mrb_obj_value(data);
}

static mrb_value mrb_sprite_make_demo_sprite(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = (CF_Sprite*) mrb_malloc(mrb, sizeof(CF_Sprite));
  *sprite = cf_make_demo_sprite();

  struct RClass* cute_module = mrb_module_get(mrb, "Cute");
  struct RData* data = mrb_data_object_alloc(mrb, mrb_class_get_under(mrb, cute_module, "Sprite"), sprite, &mrb_sprite_type);
  return mrb_obj_value(data);
}

static mrb_value mrb_sprite_draw(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = DATA_PTR(self);
  if (!sprite) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Sprite is not initialized");
  }

  cf_draw_sprite(sprite);
  return mrb_nil_value();
}

static mrb_value mrb_sprite_play(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = DATA_PTR(self);
  if (!sprite) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Sprite is not initialized");
  }

  char* animation_name;
  mrb_get_args(mrb, "z", &animation_name);

  cf_sprite_play(sprite, animation_name);
  return self;
}

static mrb_value mrb_sprite_update(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = DATA_PTR(self);
  if (!sprite) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Sprite is not initialized");
  }

  cf_sprite_update(sprite);
  return self;
}

static mrb_value mrb_sprite_is_playing(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite = DATA_PTR(self);
  if (!sprite) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "Sprite is not initialized");
  }

  char* animation_name;
  mrb_get_args(mrb, "z", &animation_name);

  bool is_playing = cf_sprite_is_playing(sprite, animation_name);
  return mrb_bool_value(is_playing);
}

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* cute_module)
{
  struct RClass* sprite_class = mrb_define_class_under(mrb, cute_module, "Sprite", mrb->object_class);
  MRB_SET_INSTANCE_TT(sprite_class, MRB_TT_DATA);

  mrb_define_class_method(mrb, sprite_class, "make_sprite", mrb_sprite_make_sprite, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, sprite_class, "make_demo_sprite", mrb_sprite_make_demo_sprite, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "draw", mrb_sprite_draw, MRB_ARGS_NONE());
  mrb_define_method(mrb, sprite_class, "play", mrb_sprite_play, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sprite_class, "playing?", mrb_sprite_is_playing, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, sprite_class, "update", mrb_sprite_update, MRB_ARGS_NONE());
}
