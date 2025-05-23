#pragma once

#include <cute.h>
#include <mruby.h>

extern struct RClass* cAudio;
extern struct RClass* cSound;

void mrb_cute_audio_init(mrb_state* mrb, struct RClass* mCute);

// Audio wrapper functions
mrb_value mrb_cf_audio_wrap(mrb_state* mrb, CF_Audio* audio);
CF_Audio* mrb_cf_audio_unwrap(mrb_state* mrb, mrb_value self);

// Sound wrapper functions
mrb_value mrb_cf_sound_wrap(mrb_state* mrb, CF_Sound* sound);
CF_Sound* mrb_cf_sound_unwrap(mrb_state* mrb, mrb_value self);