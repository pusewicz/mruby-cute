#pragma once

#include <cute.h>
#include <mruby.h>

struct RClass* cSprite;

void mrb_cute_sprite_init(mrb_state* mrb, struct RClass* mCute);
