#include "audio.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>
#include <mruby/string.h>
#include <mruby/variable.h>

struct RClass* cAudio;
struct RClass* cSound;

// Audio data type
static void mrb_cf_audio_free(mrb_state* mrb, void* p)
{
    CF_Audio* audio = (CF_Audio*)p;
    if (audio) {
        cf_audio_destroy(audio);
        mrb_free(mrb, audio);
    }
}

static const struct mrb_data_type mrb_cf_audio_type = {
    "CF_Audio", mrb_cf_audio_free
};

// Sound data type
static void mrb_cf_sound_free(mrb_state* mrb, void* p)
{
    CF_Sound* sound = (CF_Sound*)p;
    if (sound) {
        mrb_free(mrb, sound);
    }
}

static const struct mrb_data_type mrb_cf_sound_type = {
    "CF_Sound", mrb_cf_sound_free
};

// Audio wrapper functions
mrb_value mrb_cf_audio_wrap(mrb_state* mrb, CF_Audio* audio)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cAudio, &mrb_cf_audio_type, audio));
}

CF_Audio* mrb_cf_audio_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio = DATA_PTR(self);
    if (audio == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized audio data");
    }
    return audio;
}

// Sound wrapper functions
mrb_value mrb_cf_sound_wrap(mrb_state* mrb, CF_Sound* sound)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cSound, &mrb_cf_sound_type, sound));
}

CF_Sound* mrb_cf_sound_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = DATA_PTR(self);
    if (sound == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized sound data");
    }
    return sound;
}

// Audio class methods
static mrb_value mrb_cf_audio_initialize(mrb_state* mrb, mrb_value self)
{
    // Audio objects are created through loading functions, not direct initialization
    mrb_raise(mrb, E_RUNTIME_ERROR, "Audio objects must be created through load functions");
    return self;
}

static mrb_value mrb_cf_audio_channel_count(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio = mrb_cf_audio_unwrap(mrb, self);
    return mrb_fixnum_value(cf_audio_channel_count(audio));
}

static mrb_value mrb_cf_audio_sample_count(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio = mrb_cf_audio_unwrap(mrb, self);
    return mrb_fixnum_value(cf_audio_sample_count(audio));
}

static mrb_value mrb_cf_audio_sample_rate(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio = mrb_cf_audio_unwrap(mrb, self);
    return mrb_fixnum_value(cf_audio_sample_rate(audio));
}

// Sound class methods
static mrb_value mrb_cf_sound_initialize(mrb_state* mrb, mrb_value self)
{
    // Sound objects are created through playing audio, not direct initialization
    mrb_raise(mrb, E_RUNTIME_ERROR, "Sound objects are created through playing audio");
    return self;
}

static mrb_value mrb_cf_sound_get_is_looped(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_bool_value(cf_sound_get_is_looped(sound));
}

static mrb_value mrb_cf_sound_set_is_looped(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    mrb_bool looped;
    mrb_get_args(mrb, "b", &looped);
    cf_sound_set_is_looped(sound, looped);
    return mrb_bool_value(looped);
}

static mrb_value mrb_cf_sound_get_is_paused(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_bool_value(cf_sound_get_is_paused(sound));
}

static mrb_value mrb_cf_sound_set_is_paused(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    mrb_bool paused;
    mrb_get_args(mrb, "b", &paused);
    cf_sound_set_is_paused(sound, paused);
    return mrb_bool_value(paused);
}

static mrb_value mrb_cf_sound_get_pitch(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_float_value(mrb, cf_sound_get_pitch(sound));
}

static mrb_value mrb_cf_sound_set_pitch(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    mrb_float pitch;
    mrb_get_args(mrb, "f", &pitch);
    cf_sound_set_pitch(sound, pitch);
    return mrb_float_value(mrb, pitch);
}

static mrb_value mrb_cf_sound_get_sample_index(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_fixnum_value(cf_sound_get_sample_index(sound));
}

static mrb_value mrb_cf_sound_set_sample_index(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    mrb_int index;
    mrb_get_args(mrb, "i", &index);
    cf_sound_set_sample_index(sound, index);
    return mrb_fixnum_value(index);
}

static mrb_value mrb_cf_sound_get_volume(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_float_value(mrb, cf_sound_get_volume(sound));
}

static mrb_value mrb_cf_sound_set_volume(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    mrb_float volume;
    mrb_get_args(mrb, "f", &volume);
    cf_sound_set_volume(sound, volume);
    return mrb_float_value(mrb, volume);
}

static mrb_value mrb_cf_sound_is_active(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    return mrb_bool_value(cf_sound_is_active(sound));
}

static mrb_value mrb_cf_sound_stop(mrb_state* mrb, mrb_value self)
{
    CF_Sound* sound = mrb_cf_sound_unwrap(mrb, self);
    cf_sound_stop(sound);
    return mrb_nil_value();
}

// Module-level audio functions
static mrb_value mrb_cf_audio_load_ogg(mrb_state* mrb, mrb_value self)
{
    char* path;
    mrb_get_args(mrb, "z", &path);
    
    CF_Audio* audio = (CF_Audio*)mrb_malloc(mrb, sizeof(CF_Audio));
    *audio = cf_audio_load_ogg(path);
    
    return mrb_cf_audio_wrap(mrb, audio);
}

static mrb_value mrb_cf_audio_load_ogg_from_memory(mrb_state* mrb, mrb_value self)
{
    mrb_value data_val;
    mrb_int size;
    mrb_get_args(mrb, "Si", &data_val, &size);
    
    void* data = (void*)RSTRING_PTR(data_val);
    
    CF_Audio* audio = (CF_Audio*)mrb_malloc(mrb, sizeof(CF_Audio));
    *audio = cf_audio_load_ogg_from_memory(data, size);
    
    return mrb_cf_audio_wrap(mrb, audio);
}

static mrb_value mrb_cf_audio_load_wav(mrb_state* mrb, mrb_value self)
{
    char* path;
    mrb_get_args(mrb, "z", &path);
    
    CF_Audio* audio = (CF_Audio*)mrb_malloc(mrb, sizeof(CF_Audio));
    *audio = cf_audio_load_wav(path);
    
    return mrb_cf_audio_wrap(mrb, audio);
}

static mrb_value mrb_cf_audio_load_wav_from_memory(mrb_state* mrb, mrb_value self)
{
    mrb_value data_val;
    mrb_int size;
    mrb_get_args(mrb, "Si", &data_val, &size);
    
    void* data = (void*)RSTRING_PTR(data_val);
    
    CF_Audio* audio = (CF_Audio*)mrb_malloc(mrb, sizeof(CF_Audio));
    *audio = cf_audio_load_wav_from_memory(data, size);
    
    return mrb_cf_audio_wrap(mrb, audio);
}

static mrb_value mrb_cf_audio_set_global_volume(mrb_state* mrb, mrb_value self)
{
    mrb_float volume;
    mrb_get_args(mrb, "f", &volume);
    cf_audio_set_global_volume(volume);
    return mrb_float_value(mrb, volume);
}

static mrb_value mrb_cf_audio_set_pan(mrb_state* mrb, mrb_value self)
{
    mrb_float pan;
    mrb_get_args(mrb, "f", &pan);
    cf_audio_set_pan(pan);
    return mrb_float_value(mrb, pan);
}

static mrb_value mrb_cf_audio_set_pause(mrb_state* mrb, mrb_value self)
{
    mrb_bool paused;
    mrb_get_args(mrb, "b", &paused);
    cf_audio_set_pause(paused);
    return mrb_bool_value(paused);
}

static mrb_value mrb_cf_audio_set_sound_volume(mrb_state* mrb, mrb_value self)
{
    mrb_float volume;
    mrb_get_args(mrb, "f", &volume);
    cf_audio_set_sound_volume(volume);
    return mrb_float_value(mrb, volume);
}

static mrb_value mrb_cf_audio_cull_duplicates(mrb_state* mrb, mrb_value self)
{
    cf_audio_cull_duplicates();
    return mrb_nil_value();
}

static mrb_value mrb_cf_play_sound(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio;
    CF_SoundParams params;
    mrb_value audio_val;
    
    mrb_get_args(mrb, "o", &audio_val);
    audio = mrb_cf_audio_unwrap(mrb, audio_val);
    params = cf_sound_params_defaults();
    
    CF_Sound* sound = (CF_Sound*)mrb_malloc(mrb, sizeof(CF_Sound));
    *sound = cf_play_sound(audio, params);
    
    return mrb_cf_sound_wrap(mrb, sound);
}

static mrb_value mrb_cf_sound_params_defaults(mrb_state* mrb, mrb_value self)
{
    // For now, return nil as we haven't implemented CF_SoundParams wrapper yet
    // TODO: Implement CF_SoundParams wrapper
    return mrb_nil_value();
}

// Music functions
static mrb_value mrb_cf_music_crossfade(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio_a;
    CF_Audio* audio_b;
    mrb_float fade_out_time, fade_in_time;
    mrb_value audio_a_val, audio_b_val;
    
    mrb_get_args(mrb, "ooff", &audio_a_val, &audio_b_val, &fade_out_time, &fade_in_time);
    
    audio_a = mrb_cf_audio_unwrap(mrb, audio_a_val);
    audio_b = mrb_cf_audio_unwrap(mrb, audio_b_val);
    
    cf_music_crossfade(audio_a, audio_b, fade_out_time, fade_in_time);
    return mrb_nil_value();
}

static mrb_value mrb_cf_music_get_sample_index(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(cf_music_get_sample_index());
}

static mrb_value mrb_cf_music_pause(mrb_state* mrb, mrb_value self)
{
    cf_music_pause();
    return mrb_nil_value();
}

static mrb_value mrb_cf_music_play(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio;
    mrb_value audio_val;
    mrb_get_args(mrb, "o", &audio_val);
    
    audio = mrb_cf_audio_unwrap(mrb, audio_val);
    cf_music_play(audio);
    return mrb_nil_value();
}

static mrb_value mrb_cf_music_resume(mrb_state* mrb, mrb_value self)
{
    cf_music_resume();
    return mrb_nil_value();
}

static mrb_value mrb_cf_music_set_loop(mrb_state* mrb, mrb_value self)
{
    mrb_bool loop;
    mrb_get_args(mrb, "b", &loop);
    cf_music_set_loop(loop);
    return mrb_bool_value(loop);
}

static mrb_value mrb_cf_music_set_pitch(mrb_state* mrb, mrb_value self)
{
    mrb_float pitch;
    mrb_get_args(mrb, "f", &pitch);
    cf_music_set_pitch(pitch);
    return mrb_float_value(mrb, pitch);
}

static mrb_value mrb_cf_music_set_sample_index(mrb_state* mrb, mrb_value self)
{
    mrb_int index;
    mrb_get_args(mrb, "i", &index);
    cf_music_set_sample_index(index);
    return mrb_fixnum_value(index);
}

static mrb_value mrb_cf_music_set_volume(mrb_state* mrb, mrb_value self)
{
    mrb_float volume;
    mrb_get_args(mrb, "f", &volume);
    cf_music_set_volume(volume);
    return mrb_float_value(mrb, volume);
}

static mrb_value mrb_cf_music_stop(mrb_state* mrb, mrb_value self)
{
    cf_music_stop();
    return mrb_nil_value();
}

static mrb_value mrb_cf_music_switch_to(mrb_state* mrb, mrb_value self)
{
    CF_Audio* audio;
    mrb_value audio_val;
    mrb_get_args(mrb, "o", &audio_val);
    
    audio = mrb_cf_audio_unwrap(mrb, audio_val);
    cf_music_switch_to(audio);
    return mrb_nil_value();
}

void mrb_cute_audio_init(mrb_state* mrb, struct RClass* mCute)
{
    // Audio class
    cAudio = mrb_define_class_under_id(mrb, mCute, MRB_SYM(Audio), mrb->object_class);
    MRB_SET_INSTANCE_TT(cAudio, MRB_TT_CDATA);
    
    mrb_define_method_id(mrb, cAudio, MRB_SYM(initialize), mrb_cf_audio_initialize, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cAudio, MRB_SYM(channel_count), mrb_cf_audio_channel_count, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cAudio, MRB_SYM(sample_count), mrb_cf_audio_sample_count, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cAudio, MRB_SYM(sample_rate), mrb_cf_audio_sample_rate, MRB_ARGS_NONE());
    
    // Sound class
    cSound = mrb_define_class_under_id(mrb, mCute, MRB_SYM(Sound), mrb->object_class);
    MRB_SET_INSTANCE_TT(cSound, MRB_TT_CDATA);
    
    mrb_define_method_id(mrb, cSound, MRB_SYM(initialize), mrb_cf_sound_initialize, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_Q(looped), mrb_cf_sound_get_is_looped, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_E(looped), mrb_cf_sound_set_is_looped, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSound, MRB_SYM_Q(paused), mrb_cf_sound_get_is_paused, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_E(paused), mrb_cf_sound_set_is_paused, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSound, MRB_SYM(pitch), mrb_cf_sound_get_pitch, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_E(pitch), mrb_cf_sound_set_pitch, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSound, MRB_SYM(sample_index), mrb_cf_sound_get_sample_index, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_E(sample_index), mrb_cf_sound_set_sample_index, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSound, MRB_SYM(volume), mrb_cf_sound_get_volume, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM_E(volume), mrb_cf_sound_set_volume, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cSound, MRB_SYM_Q(active), mrb_cf_sound_is_active, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cSound, MRB_SYM(stop), mrb_cf_sound_stop, MRB_ARGS_NONE());
    
    // Audio module functions
    mrb_define_module_function(mrb, mCute, "cf_audio_load_ogg", mrb_cf_audio_load_ogg, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_load_ogg_from_memory", mrb_cf_audio_load_ogg_from_memory, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_audio_load_wav", mrb_cf_audio_load_wav, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_load_wav_from_memory", mrb_cf_audio_load_wav_from_memory, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_audio_set_global_volume", mrb_cf_audio_set_global_volume, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_set_pan", mrb_cf_audio_set_pan, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_set_pause", mrb_cf_audio_set_pause, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_set_sound_volume", mrb_cf_audio_set_sound_volume, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_audio_cull_duplicates", mrb_cf_audio_cull_duplicates, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_play_sound", mrb_cf_play_sound, MRB_ARGS_ARG(1, 1));
    mrb_define_module_function(mrb, mCute, "cf_sound_params_defaults", mrb_cf_sound_params_defaults, MRB_ARGS_NONE());
    
    // Music functions
    mrb_define_module_function(mrb, mCute, "cf_music_crossfade", mrb_cf_music_crossfade, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mCute, "cf_music_get_sample_index", mrb_cf_music_get_sample_index, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_music_pause", mrb_cf_music_pause, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_music_play", mrb_cf_music_play, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_music_resume", mrb_cf_music_resume, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_music_set_loop", mrb_cf_music_set_loop, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_music_set_pitch", mrb_cf_music_set_pitch, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_music_set_sample_index", mrb_cf_music_set_sample_index, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_music_set_volume", mrb_cf_music_set_volume, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_music_stop", mrb_cf_music_stop, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_music_switch_to", mrb_cf_music_switch_to, MRB_ARGS_REQ(1));
    
    // TODO: Implement callback functions when needed:
    // - cf_music_set_on_finish_callback
    // - cf_sound_set_on_finish_callback
}