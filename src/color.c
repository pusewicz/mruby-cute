#include "color.h"
#include <mruby/class.h>
#include <mruby/data.h>
#include <mruby/presym.h>

// Color implementation
static void mrb_cf_color_free(mrb_state* mrb, void* p)
{
    CF_Color* data = (CF_Color*)p;
    mrb_free(mrb, data);
}

const struct mrb_data_type mrb_cf_color_data_type = { "CF_Color", mrb_cf_color_free };

static mrb_value mrb_cf_color_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
    mrb_get_args(mrb, "|ffff", &r, &g, &b, &a);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_rgba_f(r, g, b, a);

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_color_data_type;

    return self;
}

static mrb_value mrb_cf_color_get_r(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = DATA_PTR(self);
    return mrb_float_value(mrb, data->r);
}

static mrb_value mrb_cf_color_set_r(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    mrb_float r;
    mrb_get_args(mrb, "f", &r);
    data->r = r;
    return mrb_float_value(mrb, data->r);
}

static mrb_value mrb_cf_color_get_g(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    return mrb_float_value(mrb, data->g);
}

static mrb_value mrb_cf_color_set_g(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    mrb_float g;
    mrb_get_args(mrb, "f", &g);
    data->g = g;
    return mrb_float_value(mrb, data->g);
}

static mrb_value mrb_cf_color_get_b(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    return mrb_float_value(mrb, data->b);
}

static mrb_value mrb_cf_color_set_b(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    mrb_float b;
    mrb_get_args(mrb, "f", &b);
    data->b = b;
    return mrb_float_value(mrb, data->b);
}

static mrb_value mrb_cf_color_get_a(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    return mrb_float_value(mrb, data->a);
}

static mrb_value mrb_cf_color_set_a(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    mrb_float a;
    mrb_get_args(mrb, "f", &a);
    data->a = a;
    return mrb_float_value(mrb, data->a);
}

static mrb_value mrb_cf_color_to_s(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    char buf[64];

    snprintf(buf, sizeof(buf), "Color(%.3f, %.3f, %.3f, %.3f)", data->r, data->g, data->b, data->a);
    return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_color_inspect(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)DATA_PTR(self);
    char buf[100];

    snprintf(buf, sizeof(buf), "#<Cute::Color:0x%lx r=%.3f g=%.3f b=%.3f a=%.3f>",
        (unsigned long)data, data->r, data->g, data->b, data->a);
    return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_color_wrap(mrb_state* mrb, CF_Color* color)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cColor, &mrb_cf_color_data_type, color));
}

CF_Color* mrb_cf_color_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;

    data = (CF_Color*)DATA_PTR(self);
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized color data");
    }

    return data;
}

// Factory methods for Color
static mrb_value mrb_cf_color_rgb_f(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_float r, g, b;

    mrb_get_args(mrb, "fff", &r, &g, &b);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_rgb_f(r, g, b);

    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_rgba_f(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_float r, g, b, a;

    mrb_get_args(mrb, "ffff", &r, &g, &b, &a);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_rgba_f(r, g, b, a);

    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_rgb(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_int r, g, b;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b);

    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_rgba(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_int r, g, b, a;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &a);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);

    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_hex(mrb_state* mrb, mrb_value self)
{
    CF_Color* data;
    mrb_int hex;

    mrb_get_args(mrb, "i", &hex);

    data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_make_color_hex((int)hex);

    return mrb_cf_color_wrap(mrb, data);
}

// Predefined colors
static mrb_value mrb_cf_color_clear(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_clear();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_black(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_black();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_white(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_white();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_red(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_red();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_green(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_green();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_blue(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_blue();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_yellow(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_yellow();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_cyan(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_cyan();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_magenta(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_magenta();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_grey(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_grey();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_orange(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_orange();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_purple(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_purple();
    return mrb_cf_color_wrap(mrb, data);
}

static mrb_value mrb_cf_color_brown(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *data = cf_color_brown();
    return mrb_cf_color_wrap(mrb, data);
}

// Color operations
static mrb_value mrb_cf_color_mul(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = mrb_cf_color_unwrap(mrb, self);
    CF_Color* result;
    mrb_float s;

    mrb_get_args(mrb, "f", &s);

    result = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *result = cf_mul_color(*data, s);

    return mrb_cf_color_wrap(mrb, result);
}

static mrb_value mrb_cf_color_add(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = mrb_cf_color_unwrap(mrb, self);
    CF_Color* other;
    CF_Color* result;
    mrb_value other_obj;

    mrb_get_args(mrb, "o", &other_obj);
    other = mrb_cf_color_unwrap(mrb, other_obj);

    result = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *result = cf_add_color(*data, *other);

    return mrb_cf_color_wrap(mrb, result);
}

static mrb_value mrb_cf_color_sub(mrb_state* mrb, mrb_value self)
{
    CF_Color* data = mrb_cf_color_unwrap(mrb, self);
    CF_Color* other;
    CF_Color* result;
    mrb_value other_obj;

    mrb_get_args(mrb, "o", &other_obj);
    other = mrb_cf_color_unwrap(mrb, other_obj);

    result = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));
    *result = cf_sub_color(*data, *other);

    return mrb_cf_color_wrap(mrb, result);
}

// Pixel implementation
static void mrb_cf_pixel_free(mrb_state* mrb, void* p)
{
    CF_Pixel* data = (CF_Pixel*)p;
    mrb_free(mrb, data);
}

const struct mrb_data_type mrb_cf_pixel_data_type = { "CF_Pixel", mrb_cf_pixel_free };

static mrb_value mrb_cf_pixel_initialize(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data;
    mrb_int r = 0, g = 0, b = 0, a = 255;
    mrb_get_args(mrb, "|iiii", &r, &g, &b, &a);

    data = (CF_Pixel*)mrb_malloc(mrb, sizeof(CF_Pixel));
    *data = cf_make_pixel_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);

    DATA_PTR(self) = data;
    DATA_TYPE(self) = &mrb_cf_pixel_data_type;

    return self;
}

static mrb_value mrb_cf_pixel_get_r(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = DATA_PTR(self);
    return mrb_fixnum_value(data->colors.r);
}

static mrb_value mrb_cf_pixel_set_r(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    mrb_int r;
    mrb_get_args(mrb, "i", &r);
    data->colors.r = (uint8_t)r;
    return mrb_fixnum_value(data->colors.r);
}

static mrb_value mrb_cf_pixel_get_g(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    return mrb_fixnum_value(data->colors.g);
}

static mrb_value mrb_cf_pixel_set_g(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    mrb_int g;
    mrb_get_args(mrb, "i", &g);
    data->colors.g = (uint8_t)g;
    return mrb_fixnum_value(data->colors.g);
}

static mrb_value mrb_cf_pixel_get_b(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    return mrb_fixnum_value(data->colors.b);
}

static mrb_value mrb_cf_pixel_set_b(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    mrb_int b;
    mrb_get_args(mrb, "i", &b);
    data->colors.b = (uint8_t)b;
    return mrb_fixnum_value(data->colors.b);
}

static mrb_value mrb_cf_pixel_get_a(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    return mrb_fixnum_value(data->colors.a);
}

static mrb_value mrb_cf_pixel_set_a(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    mrb_int a;
    mrb_get_args(mrb, "i", &a);
    data->colors.a = (uint8_t)a;
    return mrb_fixnum_value(data->colors.a);
}

static mrb_value mrb_cf_pixel_to_s(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    char buf[64];

    snprintf(buf, sizeof(buf), "Pixel(%d, %d, %d, %d)",
        data->colors.r, data->colors.g, data->colors.b, data->colors.a);
    return mrb_str_new_cstr(mrb, buf);
}

static mrb_value mrb_cf_pixel_inspect(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data = (CF_Pixel*)DATA_PTR(self);
    char buf[100];

    snprintf(buf, sizeof(buf), "#<Cute::Pixel:0x%lx r=%d g=%d b=%d a=%d>",
        (unsigned long)data, data->colors.r, data->colors.g, data->colors.b, data->colors.a);
    return mrb_str_new_cstr(mrb, buf);
}

mrb_value mrb_cf_pixel_wrap(mrb_state* mrb, CF_Pixel* pixel)
{
    return mrb_obj_value(Data_Wrap_Struct(mrb, cPixel, &mrb_cf_pixel_data_type, pixel));
}

CF_Pixel* mrb_cf_pixel_unwrap(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data;

    data = (CF_Pixel*)DATA_PTR(self);
    if (data == NULL) {
        mrb_raise(mrb, E_RUNTIME_ERROR, "uninitialized pixel data");
    }

    return data;
}

// Factory methods for Pixel
static mrb_value mrb_cf_pixel_rgb(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data;
    mrb_int r, g, b;

    mrb_get_args(mrb, "iii", &r, &g, &b);

    data = (CF_Pixel*)mrb_malloc(mrb, sizeof(CF_Pixel));
    *data = cf_make_pixel_rgb((uint8_t)r, (uint8_t)g, (uint8_t)b);

    return mrb_cf_pixel_wrap(mrb, data);
}

static mrb_value mrb_cf_pixel_rgba(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data;
    mrb_int r, g, b, a;

    mrb_get_args(mrb, "iiii", &r, &g, &b, &a);

    data = (CF_Pixel*)mrb_malloc(mrb, sizeof(CF_Pixel));
    *data = cf_make_pixel_rgba((uint8_t)r, (uint8_t)g, (uint8_t)b, (uint8_t)a);

    return mrb_cf_pixel_wrap(mrb, data);
}

static mrb_value mrb_cf_pixel_hex(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* data;
    mrb_int hex;

    mrb_get_args(mrb, "i", &hex);

    data = (CF_Pixel*)mrb_malloc(mrb, sizeof(CF_Pixel));
    *data = cf_make_pixel_hex((int)hex);

    return mrb_cf_pixel_wrap(mrb, data);
}

// Conversion methods
static mrb_value mrb_cf_color_to_pixel(mrb_state* mrb, mrb_value self)
{
    CF_Color* color = mrb_cf_color_unwrap(mrb, self);
    CF_Pixel* pixel = (CF_Pixel*)mrb_malloc(mrb, sizeof(CF_Pixel));

    *pixel = cf_color_to_pixel(*color);

    return mrb_cf_pixel_wrap(mrb, pixel);
}

static mrb_value mrb_cf_pixel_to_color(mrb_state* mrb, mrb_value self)
{
    CF_Pixel* pixel = mrb_cf_pixel_unwrap(mrb, self);
    CF_Color* color = (CF_Color*)mrb_malloc(mrb, sizeof(CF_Color));

    *color = cf_pixel_to_color(*pixel);

    return mrb_cf_color_wrap(mrb, color);
}

// Initializing the module
void mrb_cute_color_init(mrb_state* mrb, struct RClass* mCute)
{
    // Color class
    cColor = mrb_define_class_under_id(mrb, mCute, MRB_SYM(Color), mrb->object_class);
    MRB_SET_INSTANCE_TT(cColor, MRB_TT_DATA);

    mrb_define_method_id(mrb, cColor, MRB_SYM(initialize), mrb_cf_color_initialize, MRB_ARGS_OPT(4));
    mrb_define_method_id(mrb, cColor, MRB_SYM(r), mrb_cf_color_get_r, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cColor, MRB_SYM_E(r), mrb_cf_color_set_r, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cColor, MRB_SYM(g), mrb_cf_color_get_g, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cColor, MRB_SYM_E(g), mrb_cf_color_set_g, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cColor, MRB_SYM(b), mrb_cf_color_get_b, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cColor, MRB_SYM_E(b), mrb_cf_color_set_b, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cColor, MRB_SYM(a), mrb_cf_color_get_a, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cColor, MRB_SYM_E(a), mrb_cf_color_set_a, MRB_ARGS_REQ(1));
    mrb_define_method_id(mrb, cColor, MRB_SYM(to_s), mrb_cf_color_to_s, MRB_ARGS_NONE());
    mrb_define_method_id(mrb, cColor, MRB_SYM(inspect), mrb_cf_color_inspect, MRB_ARGS_NONE());

    // Color operations
    // TODO: Convert these to proper object operators
    mrb_define_method(mrb, cColor, "mul", mrb_cf_color_mul, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cColor, "add", mrb_cf_color_add, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cColor, "sub", mrb_cf_color_sub, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cColor, "to_pixel", mrb_cf_color_to_pixel, MRB_ARGS_NONE());

    // Factory methods for Color
    // TODO: Rename these to match CF
    mrb_define_module_function(mrb, mCute, "rgb_f", mrb_cf_color_rgb_f, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "rgba_f", mrb_cf_color_rgba_f, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mCute, "rgb", mrb_cf_color_rgb, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "rgba", mrb_cf_color_rgba, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mCute, "color_hex", mrb_cf_color_hex, MRB_ARGS_REQ(1));

    // Predefined colors
    // TODO: Rename these to match CF
    mrb_define_module_function(mrb, mCute, "color_clear", mrb_cf_color_clear, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_black", mrb_cf_color_black, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_white", mrb_cf_color_white, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_red", mrb_cf_color_red, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_green", mrb_cf_color_green, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_blue", mrb_cf_color_blue, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_yellow", mrb_cf_color_yellow, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_cyan", mrb_cf_color_cyan, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_magenta", mrb_cf_color_magenta, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_grey", mrb_cf_color_grey, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_orange", mrb_cf_color_orange, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_purple", mrb_cf_color_purple, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mCute, "color_brown", mrb_cf_color_brown, MRB_ARGS_NONE());

    // Pixel class
    cPixel = mrb_define_class_under(mrb, mCute, "Pixel", mrb->object_class);
    MRB_SET_INSTANCE_TT(cPixel, MRB_TT_DATA);

    mrb_define_method(mrb, cPixel, "initialize", mrb_cf_pixel_initialize, MRB_ARGS_OPT(4));
    mrb_define_method(mrb, cPixel, "r", mrb_cf_pixel_get_r, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "r=", mrb_cf_pixel_set_r, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cPixel, "g", mrb_cf_pixel_get_g, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "g=", mrb_cf_pixel_set_g, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cPixel, "b", mrb_cf_pixel_get_b, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "b=", mrb_cf_pixel_set_b, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cPixel, "a", mrb_cf_pixel_get_a, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "a=", mrb_cf_pixel_set_a, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cPixel, "to_s", mrb_cf_pixel_to_s, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "inspect", mrb_cf_pixel_inspect, MRB_ARGS_NONE());
    mrb_define_method(mrb, cPixel, "to_color", mrb_cf_pixel_to_color, MRB_ARGS_NONE());

    // Factory methods for Pixel
    mrb_define_module_function(mrb, mCute, "pixel_rgb", mrb_cf_pixel_rgb, MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mCute, "pixel_rgba", mrb_cf_pixel_rgba, MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mCute, "pixel_hex", mrb_cf_pixel_hex, MRB_ARGS_REQ(1));
}
