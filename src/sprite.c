#include "mruby-cute.h"
#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/string.h>

static const struct mrb_data_type mrb_cf_sprite_type = {"CF_Sprite", mrb_free};

/*
 * CF_Sprite
 */

static mrb_value mrb_cf_sprite_initialize(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  sprite = (CF_Sprite*) mrb_malloc(mrb, sizeof(CF_Sprite));
  *sprite = cf_sprite_defaults();

  DATA_PTR(self) = sprite;
  DATA_TYPE(self) = &mrb_cf_sprite_type;

  return self;
}

static mrb_value mrb_cf_sprite_inspect(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;

  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);
  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  mrb_value str = mrb_str_new_cstr(mrb, "#<Cute::CF_Sprite");
  mrb_str_cat_cstr(mrb, str, " name:");
  mrb_str_cat_str(mrb, str, mrb_inspect(mrb, mrb_str_new_cstr(mrb, sprite->name)));
  mrb_str_cat_cstr(mrb, str, " w:");
  mrb_str_cat_str(mrb, str, mrb_inspect(mrb, mrb_fixnum_value(sprite->w)));
  mrb_str_cat_cstr(mrb, str, " h:");
  mrb_str_cat_str(mrb, str, mrb_inspect(mrb, mrb_fixnum_value(sprite->h)));
  mrb_str_cat_cstr(mrb, str, " opacity:");
  mrb_str_cat_str(mrb, str, mrb_inspect(mrb, mrb_float_value(mrb, sprite->opacity)));
  mrb_str_cat_cstr(mrb, str, ">");

  return str;
}

static mrb_value mrb_cf_sprite_get_w(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;

  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);
  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  return mrb_fixnum_value(sprite->w);
}

static mrb_value mrb_cf_sprite_set_w(mrb_state* mrb, mrb_value self)
{
  mrb_int w;
  CF_Sprite* sprite;

  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);
  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  mrb_get_args(mrb, "i", &w);

  sprite->w = w;

  return mrb_fixnum_value(sprite->w);
}

static mrb_value mrb_cf_sprite_get_h(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);

  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  return mrb_fixnum_value(sprite->h);
}

static mrb_value mrb_cf_sprite_set_h(mrb_state* mrb, mrb_value self)
{
  mrb_int h;
  CF_Sprite* sprite;

  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);
  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  mrb_get_args(mrb, "i", &h);

  sprite->h = h;

  return mrb_fixnum_value(sprite->h);
}

static mrb_value mrb_cf_sprite_get_opacity(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);

  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  return mrb_float_value(mrb, sprite->opacity);
}

static mrb_value mrb_cf_sprite_set_opacity(mrb_state* mrb, mrb_value self)
{
  mrb_float opacity;
  CF_Sprite* sprite;

  sprite = (CF_Sprite*) mrb_data_get_ptr(mrb, self, &mrb_cf_sprite_type);
  if (sprite == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized data");
  }

  mrb_get_args(mrb, "f", &opacity);

  sprite->opacity = opacity;

  return mrb_float_value(mrb, sprite->opacity);
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

static mrb_value mrb_cf_sprite_pause(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  cf_sprite_pause(sprite);
  return mrb_nil_value();
}

static mrb_value mrb_cf_sprite_unpause(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  cf_sprite_unpause(sprite);
  return mrb_nil_value();
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

// float cf_sprite_get_scale_x
static mrb_value mrb_cf_sprite_get_scale_x(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  return mrb_float_value(mrb, cf_sprite_get_scale_x(sprite));
}

// float cf_sprite_get_scale_y
static mrb_value mrb_cf_sprite_get_scale_y(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_get_args(mrb, "d", &sprite, &mrb_cf_sprite_type);
  return mrb_float_value(mrb, cf_sprite_get_scale_y(sprite));
}

// void cf_sprite_set_scale_x
static mrb_value mrb_cf_sprite_set_scale_x(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_float scale_x;
  mrb_get_args(mrb, "df", &sprite, &mrb_cf_sprite_type, &scale_x);
  cf_sprite_set_scale_x(sprite, scale_x);
  return mrb_nil_value();
}

// void cf_sprite_set_scale_y
static mrb_value mrb_cf_sprite_set_scale_y(mrb_state* mrb, mrb_value self)
{
  CF_Sprite* sprite;
  mrb_float scale_y;
  mrb_get_args(mrb, "df", &sprite, &mrb_cf_sprite_type, &scale_y);
  cf_sprite_set_scale_y(sprite, scale_y);
  return mrb_nil_value();
}

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mrb_cute_module)
{
  // CF_Sprite
  struct RClass* cf_sprite_class;
  cf_sprite_class = mrb_define_class_under(mrb, mrb_cute_module, "CF_Sprite", mrb->object_class);
  MRB_SET_INSTANCE_TT(cf_sprite_class, MRB_TT_CDATA);
  mrb_define_method(mrb, cf_sprite_class, "initialize", mrb_cf_sprite_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, cf_sprite_class, "inspect", mrb_cf_sprite_inspect, MRB_ARGS_NONE());
  mrb_define_method(mrb, cf_sprite_class, "w", mrb_cf_sprite_get_w, MRB_ARGS_NONE());
  mrb_define_method(mrb, cf_sprite_class, "w=", mrb_cf_sprite_set_w, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cf_sprite_class, "h", mrb_cf_sprite_get_h, MRB_ARGS_NONE());
  mrb_define_method(mrb, cf_sprite_class, "h=", mrb_cf_sprite_set_h, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, cf_sprite_class, "opacity", mrb_cf_sprite_get_opacity, MRB_ARGS_NONE());
  mrb_define_method(mrb, cf_sprite_class, "opacity=", mrb_cf_sprite_set_opacity, MRB_ARGS_REQ(1));

  // cute_sprite
  mrb_define_module_function(mrb, mrb_cute_module, "cf_make_demo_sprite", mrb_cf_make_demo_sprite, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_defaults", mrb_cf_sprite_defaults, MRB_ARGS_NONE());
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_draw", mrb_cf_sprite_draw, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_height", mrb_cf_sprite_height, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_is_playing", mrb_cf_sprite_is_playing, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_pause", mrb_cf_sprite_pause, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_unpause", mrb_cf_sprite_unpause, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_play", mrb_cf_sprite_play, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_update", mrb_cf_sprite_update, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_width", mrb_cf_sprite_width, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_get_scale_x", mrb_cf_sprite_get_scale_x, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_get_scale_y", mrb_cf_sprite_get_scale_y, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_set_scale_x", mrb_cf_sprite_set_scale_x, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mrb_cute_module, "cf_sprite_set_scale_y", mrb_cf_sprite_set_scale_y, MRB_ARGS_REQ(2));
}
