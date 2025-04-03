#include <cute.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/variable.h>

struct RClass* cSprite;
struct mrb_data_type const mrb_cf_sprite_data_type;

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mCute);
