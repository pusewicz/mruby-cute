#include "aabb.h"
#include "circle.h"
#include "color.h"
#include "draw.h"
#include "mrb_cute.h"
#include "sincos.h"
#include "sprite.h"
#include "transform.h"
#include "vector.h"

static mrb_value mrb_cf_version_string_linked(mrb_state* mrb, mrb_value self)
{
    return mrb_str_new_cstr(mrb, cf_version_string_linked());
}

static void mrb_cute_init(mrb_state* mrb, struct RClass* mCute)
{
    mrb_define_module_function(mrb, mCute, "cf_version_string_linked", mrb_cf_version_string_linked, MRB_ARGS_NONE());
}

void mrb_mruby_cute_gem_init(mrb_state* mrb)
{
    struct RClass* mCute = mrb_define_module(mrb, "Cute");

    mrb_cute_init(mrb, mCute);
    mrb_cute_draw_init(mrb, mCute);
    mrb_cute_v2_init(mrb, mCute);
    mrb_cute_sincos_init(mrb, mCute);
    mrb_cute_transform_init(mrb, mCute);
    mrb_cute_app_init(mrb, mCute);
    mrb_cute_result_init(mrb, mCute);
    mrb_cute_sprite_init(mrb, mCute);
    mrb_cute_input_init(mrb, mCute);
    mrb_cute_time_init(mrb, mCute);
    mrb_cute_stopwatch_init(mrb, mCute);
    mrb_cute_aabb_init(mrb, mCute);
    mrb_cute_circle_init(mrb, mCute);
    mrb_cute_color_init(mrb, mCute);
}

void mrb_mruby_cute_gem_final(mrb_state* mrb)
{
}
