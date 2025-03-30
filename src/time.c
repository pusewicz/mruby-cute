#include "mrb_cute.h"

// CF_DELTA_TIME
static mrb_value mrb_cf_delta_time(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_DELTA_TIME);
}

// CF_DELTA_TIME_INTERPOLANT
static mrb_value mrb_cf_delta_time_interpolant(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_DELTA_TIME_INTERPOLANT);
}

// CF_DELTA_TIME_FIXED
static mrb_value mrb_cf_delta_time_fixed(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_DELTA_TIME_FIXED);
}

// CF_SECONDS
static mrb_value mrb_cf_seconds(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_SECONDS);
}

// CF_PREV_SECONDS
static mrb_value mrb_cf_prev_seconds(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_PREV_SECONDS);
}

// CF_TICKS
static mrb_value mrb_cf_ticks(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(CF_TICKS);
}

// CF_PREV_TICKS
static mrb_value mrb_cf_prev_ticks(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(CF_PREV_TICKS);
}

// CF_PAUSE_TIME_LEFT
static mrb_value mrb_cf_pause_time_left(mrb_state* mrb, mrb_value self)
{
    return mrb_float_value(mrb, CF_PAUSE_TIME_LEFT);
}

// CF_API void CF_CALL cf_set_fixed_timestep(int frames_per_second);
static mrb_value mrb_cf_set_fixed_timestep(mrb_state* mrb, mrb_value self)
{
    mrb_int frames_per_second;
    mrb_get_args(mrb, "i", &frames_per_second);
    cf_set_fixed_timestep(frames_per_second);
    return mrb_nil_value();
}

// CF_API void CF_CALL cf_set_fixed_timestep_max_updates(int max_updates);
static mrb_value mrb_cf_set_fixed_timestep_max_updates(mrb_state* mrb, mrb_value self)
{
    mrb_int max_updates;
    mrb_get_args(mrb, "i", &max_updates);
    cf_set_fixed_timestep_max_updates(max_updates);
    return mrb_nil_value();
}

// CF_API void CF_CALL cf_set_target_framerate(int frames_per_second);
static mrb_value mrb_cf_set_target_framerate(mrb_state* mrb, mrb_value self)
{
    mrb_int frames_per_second;
    mrb_get_args(mrb, "i", &frames_per_second);
    cf_set_target_framerate(frames_per_second);
    return mrb_nil_value();
}

// TODO: CF_API void CF_CALL cf_set_update_udata(void* udata);
// TODO: CF_API void CF_CALL cf_update_time(CF_OnUpdateFn* on_update);

// CF_API void CF_CALL cf_pause_for(float seconds);
static mrb_value mrb_cf_pause_for(mrb_state* mrb, mrb_value self)
{
    mrb_float seconds;
    mrb_get_args(mrb, "f", &seconds);
    cf_pause_for(seconds);
    return mrb_nil_value();
}

// CF_API void CF_CALL cf_pause_for_ticks(uint64_t pause_ticks);
static mrb_value mrb_cf_pause_for_ticks(mrb_state* mrb, mrb_value self)
{
    mrb_int pause_ticks;
    mrb_get_args(mrb, "i", &pause_ticks);
    cf_pause_for_ticks(pause_ticks);
    return mrb_nil_value();
}

// CF_API bool CF_CALL cf_on_interval(float interval, float offset);
static mrb_value mrb_cf_on_interval(mrb_state* mrb, mrb_value self)
{
    mrb_float interval;
    mrb_float offset;
    mrb_get_args(mrb, "ff", &interval, &offset);
    return mrb_bool_value(cf_on_interval(interval, offset));
}

// CF_API bool CF_CALL cf_between_interval(float interval, float offset);
static mrb_value mrb_cf_between_interval(mrb_state* mrb, mrb_value self)
{
    mrb_float interval;
    mrb_float offset;
    mrb_get_args(mrb, "ff", &interval, &offset);
    return mrb_bool_value(cf_between_interval(interval, offset));
}

// CF_API bool CF_CALL cf_on_timestamp(double timestamp);
static mrb_value mrb_cf_on_timestamp(mrb_state* mrb, mrb_value self)
{
    mrb_float timestamp;
    mrb_get_args(mrb, "f", &timestamp);
    return mrb_bool_value(cf_on_timestamp(timestamp));
}

// CF_API bool CF_CALL cf_is_paused();
static mrb_value mrb_cf_is_paused(mrb_state* mrb, mrb_value self)
{
    return mrb_bool_value(cf_is_paused());
}

// CF_API uint64_t CF_CALL cf_get_ticks();
static mrb_value mrb_cf_get_ticks(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(cf_get_ticks());
}

// CF_API uint64_t CF_CALL cf_get_tick_frequency();
static mrb_value mrb_cf_get_tick_frequency(mrb_state* mrb, mrb_value self)
{
    return mrb_fixnum_value(cf_get_tick_frequency());
}

// CF_API void CF_CALL cf_sleep(int milliseconds);
static mrb_value mrb_cf_sleep(mrb_state* mrb, mrb_value self)
{
    mrb_int milliseconds;
    mrb_get_args(mrb, "i", &milliseconds);
    cf_sleep(milliseconds);
    return mrb_nil_value();
}

void mrb_cute_time_init(mrb_state* mrb, struct RClass* mCute)
{
    mrb_define_module_function(mrb, mCute, "CF_DELTA_TIME", mrb_cf_delta_time, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_DELTA_TIME_FIXED", mrb_cf_delta_time_fixed, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_DELTA_TIME_INTERPOLANT", mrb_cf_delta_time_interpolant, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_SECONDS", mrb_cf_seconds, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_PREV_SECONDS", mrb_cf_prev_seconds, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_TICKS", mrb_cf_ticks, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_PREV_TICKS", mrb_cf_prev_ticks, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "CF_PAUSE_TIME_LEFT", mrb_cf_pause_time_left, MRB_ARGS_NONE());

    mrb_define_module_function(mrb, mCute, "cf_set_fixed_timestep", mrb_cf_set_fixed_timestep, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_set_fixed_timestep_max_updates", mrb_cf_set_fixed_timestep_max_updates, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_set_target_framerate", mrb_cf_set_target_framerate, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pause_for", mrb_cf_pause_for, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_pause_for_ticks", mrb_cf_pause_for_ticks, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_on_interval", mrb_cf_on_interval, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_between_interval", mrb_cf_between_interval, MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mCute, "cf_on_timestamp", mrb_cf_on_timestamp, MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mCute, "cf_is_paused", mrb_cf_is_paused, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_get_ticks", mrb_cf_get_ticks, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_get_tick_frequency", mrb_cf_get_tick_frequency, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "cf_sleep", mrb_cf_sleep, MRB_ARGS_REQ(1));
}
