#include "mrb_cute.h"

static const struct mrb_data_type mrb_stopwatch_type = {
  "CF_Stopwatch", mrb_free
};

static mrb_value mrb_stopwatch_initialize(mrb_state *mrb, mrb_value self)
{
  CF_Stopwatch *stopwatch = (CF_Stopwatch*)mrb_malloc(mrb, sizeof(CF_Stopwatch));

  // Initialize the stopwatch (assuming cf_make_stopwatch is available)
  *stopwatch = cf_make_stopwatch();

  // Set the data pointer
  DATA_PTR(self) = stopwatch;
  DATA_TYPE(self) = &mrb_stopwatch_type;

  return self;
}

static mrb_value mrb_stopwatch_seconds(mrb_state *mrb, mrb_value self)
{
  CF_Stopwatch *stopwatch = DATA_PTR(self);
  return mrb_fixnum_value(cf_stopwatch_seconds(*stopwatch));
}

static mrb_value mrb_stopwatch_milliseconds(mrb_state *mrb, mrb_value self)
{
  CF_Stopwatch *stopwatch = DATA_PTR(self);
  return mrb_fixnum_value(cf_stopwatch_milliseconds(*stopwatch));
}

static mrb_value mrb_stopwatch_microseconds(mrb_state *mrb, mrb_value self)
{
  CF_Stopwatch *stopwatch = DATA_PTR(self);
  return mrb_fixnum_value(cf_stopwatch_microseconds(*stopwatch));
}

void mrb_cute_stopwatch_init(mrb_state* mrb, struct RClass* mrb_cute_module)
{
  struct RClass *stopwatch_class;

  // Create Stopwatch class
  stopwatch_class = mrb_define_class_under(mrb, mrb_cute_module, "Stopwatch", mrb->object_class);
  MRB_SET_INSTANCE_TT(stopwatch_class, MRB_TT_DATA);

  mrb_define_method(mrb, stopwatch_class, "initialize", mrb_stopwatch_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, stopwatch_class, "seconds", mrb_stopwatch_seconds, MRB_ARGS_NONE());
  mrb_define_method(mrb, stopwatch_class, "milliseconds", mrb_stopwatch_milliseconds, MRB_ARGS_NONE());
  mrb_define_method(mrb, stopwatch_class, "microseconds", mrb_stopwatch_microseconds, MRB_ARGS_NONE());
}
