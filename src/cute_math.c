#include "cute.h"
#include <cute_math.h>

/**
 * Struct definitions
 */
static const struct mrb_data_type CF_V2_type = { "CF_V2", mrb_free };
static const struct mrb_data_type CF_SinCos_type = { "CF_SinCos", mrb_free };
static const struct mrb_data_type CF_M2x2_type = { "CF_M2x2", mrb_free };
static const struct mrb_data_type CF_M3x2_type = { "CF_M3x2", mrb_free };
static const struct mrb_data_type CF_Transform_type = { "CF_Transform", mrb_free };
static const struct mrb_data_type CF_Halfspace_type = { "CF_Halfspace", mrb_free };
static const struct mrb_data_type CF_Ray_type = { "CF_Ray", mrb_free };
static const struct mrb_data_type CF_Raycast_type = { "CF_Raycast", mrb_free };
static const struct mrb_data_type CF_Circle_type = { "CF_Circle", mrb_free };
static const struct mrb_data_type CF_Aabb_type = { "CF_Aabb", mrb_free };
static const struct mrb_data_type CF_Rect_type = { "CF_Rect", mrb_free };
static const struct mrb_data_type CF_Poly_type = { "CF_Poly", mrb_free };
static const struct mrb_data_type CF_Capsule_type = { "CF_Capsule", mrb_free };
static const struct mrb_data_type CF_Manifold_type = { "CF_Manifold", mrb_free };
static const struct mrb_data_type CF_SliceOutput_type = { "CF_SliceOutput", mrb_free };
static const struct mrb_data_type CF_GjkCache_type = { "CF_GjkCache", mrb_free };
static const struct mrb_data_type CF_ToiResult_type = { "CF_ToiResult", mrb_free };

/**
 * Data type definitions
 */
typedef struct mrb_cf_v2_data_t {
  CF_V2* cf_v2_ptr;
} mrb_cf_v2_data_t;

typedef struct mrb_cf_sincos_data_t {
  CF_SinCos* cf_sincos_ptr;
} mrb_cf_sincos_data_t;

typedef struct mrb_cf_m2x2_data_t {
  CF_M2x2* cf_m2x2_ptr;
} mrb_cf_m2x2_data_t;

typedef struct mrb_cf_m3x2_data_t {
  CF_M3x2* cf_m3x2_ptr;
} mrb_cf_m3x2_data_t;

typedef struct mrb_cf_transform_data_t {
  CF_Transform* cf_transform_ptr;
} mrb_cf_transform_data_t;

typedef struct mrb_cf_halfspace_data_t {
  CF_Halfspace* cf_halfspace_ptr;
} mrb_cf_halfspace_data_t;

typedef struct mrb_cf_ray_data_t {
  CF_Ray* cf_ray_ptr;
} mrb_cf_ray_data_t;

typedef struct mrb_cf_raycast_data_t {
  CF_Raycast* cf_raycast_ptr;
} mrb_cf_raycast_data_t;

typedef struct mrb_cf_circle_data_t {
  CF_Circle* cf_circle_ptr;
} mrb_cf_circle_data_t;

typedef struct mrb_cf_aabb_data_t {
  CF_Aabb* cf_aabb_ptr;
} mrb_cf_aabb_data_t;

typedef struct mrb_cf_rect_data_t {
  CF_Rect* cf_rect_ptr;
} mrb_cf_rect_data_t;

typedef struct mrb_cf_poly_data_t {
  CF_Poly* cf_poly_ptr;
} mrb_cf_poly_data_t;

typedef struct mrb_cf_capsule_data_t {
  CF_Capsule* cf_capsule_ptr;
} mrb_cf_capsule_data_t;

typedef struct mrb_cf_manifold_data_t {
  CF_Manifold* cf_manifold_ptr;
} mrb_cf_manifold_data_t;

typedef struct mrb_cf_sliceoutput_data_t {
  CF_SliceOutput* cf_sliceoutput_ptr;
} mrb_cf_sliceoutput_data_t;

typedef struct mrb_cf_gjkcache_data_t {
  CF_GjkCache* cf_gjkcache_ptr;
} mrb_cf_gjkcache_data_t;

typedef struct mrb_cf_toiresult_data_t {
  CF_ToiResult* cf_toiresult_ptr;
} mrb_cf_toiresult_data_t;


/**
 * Function wrapper declarations TODO: Move to header
 */
static mrb_value mrb_cf_aabb_to_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_to_aabb_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_to_capsule(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_to_capsule_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_to_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_to_poly_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_aabb_verts(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_abs(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_abs_int(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_abs_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_add_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_angle_diff(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_area_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_area_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_atan2_360(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_atan2_360_sc(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_atan2_360_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_back_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_back_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_back_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_bezier(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_bezier2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_bottom(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_bottom_left(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_bottom_right(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_calc_area(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_capsule_to_capsule(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_capsule_to_capsule_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_capsule_to_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_capsule_to_poly_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cast_ray(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ceil(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_center(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_center_of_mass(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_centroid(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_aabb_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_capsule(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_capsule_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_circle_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_circle_to_poly_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp01(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp01_int(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp01_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_aabb_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_int(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_clamp_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_collide(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_collide_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_collided(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_combine(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_contains_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_contains_point(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cross(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cross_f_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cross_v2_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cube_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cube_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cube_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_cw90(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_det2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_distance(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_distance_hs(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_distance_sq(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_div_v2_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_dot(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_endpoint(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_expand_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_expand_aabb_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_extents(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_fit_power_of_two(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_floor(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_fract(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_from_angle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_gjk(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_greater_equal_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_greater_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_half_extents(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_half_height(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_half_width(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_height(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_hmax(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_hmin(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_hull(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_impact(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_inflate(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_intersect(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_intersect_halfspace(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_intersect_halfspace2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_intersect_halfspace3(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_invert(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_is_even(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_is_odd(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_is_power_of_two(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_is_power_of_two_uint(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_left(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_len(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_len_sq(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_lerp(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_lerp_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_lesser_equal_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_lesser_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_aabb_center_half_extents(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_aabb_from_top_left(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_aabb_pos_w_h(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_aabb_verts(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_capsule(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_capsule2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_identity(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_ray(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_rotation(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_scale(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_scale_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_scale_translation(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_scale_translation_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_scale_translation_f_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_transform(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_transform_TR(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_transform_TSR(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_translation(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_make_translation_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_max_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_max_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_midpoint(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_min_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_min_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mod(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mulT_sc(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mulT_sc_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mulT_tf(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mulT_tf_hs(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mulT_tf_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_m2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_m2_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_m2_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_m32(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_m32_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_sc(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_sc_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_tf(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_tf_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_tf_hs(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_tf_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_mul_v2_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_neg_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_norm(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_norms(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_origin(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ortho_2d(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_overlaps(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_parallel(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_parallel2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_perp(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_plane(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_plane2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_poly_to_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_poly_to_poly_manifold(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_project(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quad_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quad_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quad_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quart_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quart_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quart_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quint_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quint_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_quint_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ray_to_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ray_to_capsule(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ray_to_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ray_to_halfspace(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_ray_to_poly(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_reflect_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_remap(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_remap01(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_right(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_round(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_safe_invert(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_safe_invert_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_safe_norm(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_safe_norm_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_safe_norm_int(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_shift(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_shortest_arc(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sign(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sign_int(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sign_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sin_in(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sin_in_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sin_out(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sincos(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sincos_f(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_skew(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_slice(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_smoothstep(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_sub_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_surface_area_aabb(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_surface_area_circle(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_toi(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_top(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_top_left(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_top_right(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_v2(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_width(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_x_axis(mrb_state *mrb, mrb_value self);
static mrb_value mrb_cf_y_axis(mrb_state *mrb, mrb_value self);

/**
 * Function wrappers
 */
/*  */
static mrb_value mrb_cf_aabb_to_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Aabb c_A = mrb_cptr(A);
  CF_Aabb c_B = mrb_cptr(B);

  bool result = cf_aabb_to_aabb(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_aabb_to_aabb_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Aabb c_A = mrb_cptr(A);
  CF_Aabb c_B = mrb_cptr(B);

  CF_Manifold result = cf_aabb_to_aabb_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_aabb_to_capsule(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Aabb c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  bool result = cf_aabb_to_capsule(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_aabb_to_capsule_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Aabb c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  CF_Manifold result = cf_aabb_to_capsule_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_aabb_to_poly(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Aabb c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  bool result = cf_aabb_to_poly(c_A, c_B, c_bx);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_aabb_to_poly_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Aabb c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  CF_Manifold result = cf_aabb_to_poly_manifold(c_A, c_B, c_bx);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_aabb_verts(mrb_state *mrb, mrb_value self) {
  mrb_value out, bb;

  mrb_get_args(mrb, "oo", &out, &bb);

  CF_V2* c_out = mrb_cptr(out);
  CF_Aabb c_bb = mrb_cptr(bb);

  cf_aabb_verts(c_out, c_bb);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_abs(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  float c_a = mrb_float(a);

  float result = cf_abs(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_abs_int(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  int result = cf_abs_int(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_abs_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_abs_v2(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_add_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_add_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_angle_diff(mrb_state *mrb, mrb_value self) {
  mrb_value radians_a, radians_b;

  mrb_get_args(mrb, "oo", &radians_a, &radians_b);

  float c_radians_a = mrb_float(radians_a);
  float c_radians_b = mrb_float(radians_b);

  float result = cf_angle_diff(c_radians_a, c_radians_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_area_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_area_aabb(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_area_circle(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Circle c_c = mrb_cptr(c);

  float result = cf_area_circle(c_c);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_atan2_360(mrb_state *mrb, mrb_value self) {
  mrb_value y, x;

  mrb_get_args(mrb, "oo", &y, &x);

  float c_y = mrb_float(y);
  float c_x = mrb_float(x);

  float result = cf_atan2_360(c_y, c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_atan2_360_sc(mrb_state *mrb, mrb_value self) {
  mrb_value r;

  mrb_get_args(mrb, "o", &r);

  CF_SinCos c_r = mrb_cptr(r);

  float result = cf_atan2_360_sc(c_r);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_atan2_360_v2(mrb_state *mrb, mrb_value self) {
  mrb_value v;

  mrb_get_args(mrb, "o", &v);

  CF_V2 c_v = mrb_cptr(v);

  float result = cf_atan2_360_v2(c_v);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_back_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_back_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_back_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_back_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_back_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_back_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_bezier(mrb_state *mrb, mrb_value self) {
  mrb_value a, c0, b, t;

  mrb_get_args(mrb, "oooo", &a, &c0, &b, &t);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_c0 = mrb_cptr(c0);
  CF_V2 c_b = mrb_cptr(b);
  float c_t = mrb_float(t);

  CF_V2 result = cf_bezier(c_a, c_c0, c_b, c_t);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_bezier2(mrb_state *mrb, mrb_value self) {
  mrb_value a, c0, c1, b, t;

  mrb_get_args(mrb, "ooooo", &a, &c0, &c1, &b, &t);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_c0 = mrb_cptr(c0);
  CF_V2 c_c1 = mrb_cptr(c1);
  CF_V2 c_b = mrb_cptr(b);
  float c_t = mrb_float(t);

  CF_V2 result = cf_bezier2(c_a, c_c0, c_c1, c_b, c_t);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_bottom(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_bottom(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_bottom_left(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_bottom_left(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_bottom_right(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_bottom_right(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_calc_area(mrb_state *mrb, mrb_value self) {
  mrb_value poly;

  mrb_get_args(mrb, "o", &poly);

  CF_Poly c_poly = mrb_cptr(poly);

  float result = cf_calc_area(c_poly);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_capsule_to_capsule(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Capsule c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  bool result = cf_capsule_to_capsule(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_capsule_to_capsule_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Capsule c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  CF_Manifold result = cf_capsule_to_capsule_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_capsule_to_poly(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Capsule c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  bool result = cf_capsule_to_poly(c_A, c_B, c_bx);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_capsule_to_poly_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Capsule c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  CF_Manifold result = cf_capsule_to_poly_manifold(c_A, c_B, c_bx);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cast_ray(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx, typeB, out;

  mrb_get_args(mrb, "ooooo", &A, &B, &bx, &typeB, &out);

  CF_Ray c_A = mrb_cptr(A);
  const void* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);
  CF_ShapeType c_typeB = mrb_cptr(typeB);
  CF_Raycast* c_out = mrb_cptr(out);

  bool result = cf_cast_ray(c_A, c_B, c_bx, c_typeB, c_out);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_ceil(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_ceil(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_center(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_center(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_center_of_mass(mrb_state *mrb, mrb_value self) {
  mrb_value poly;

  mrb_get_args(mrb, "o", &poly);

  CF_Poly c_poly = mrb_cptr(poly);

  CF_V2 result = cf_center_of_mass(c_poly);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_centroid(mrb_state *mrb, mrb_value self) {
  mrb_value verts, count;

  mrb_get_args(mrb, "oo", &verts, &count);

  const CF_V2* c_verts = mrb_cptr(verts);
  int c_count = mrb_fixnum(count);

  CF_V2 result = cf_centroid(c_verts, c_count);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_circle_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_circle_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_circle_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_to_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Aabb c_B = mrb_cptr(B);

  bool result = cf_circle_to_aabb(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_circle_to_aabb_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Aabb c_B = mrb_cptr(B);

  CF_Manifold result = cf_circle_to_aabb_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_to_capsule(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  bool result = cf_circle_to_capsule(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_circle_to_capsule_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  CF_Manifold result = cf_circle_to_capsule_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_to_circle(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Circle c_B = mrb_cptr(B);

  bool result = cf_circle_to_circle(c_A, c_B);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_circle_to_circle_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Circle c_A = mrb_cptr(A);
  CF_Circle c_B = mrb_cptr(B);

  CF_Manifold result = cf_circle_to_circle_manifold(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_circle_to_poly(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Circle c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  bool result = cf_circle_to_poly(c_A, c_B, c_bx);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_circle_to_poly_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx;

  mrb_get_args(mrb, "ooo", &A, &B, &bx);

  CF_Circle c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  CF_Manifold result = cf_circle_to_poly_manifold(c_A, c_B, c_bx);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp(mrb_state *mrb, mrb_value self) {
  mrb_value a, lo, hi;

  mrb_get_args(mrb, "ooo", &a, &lo, &hi);

  float c_a = mrb_float(a);
  float c_lo = mrb_float(lo);
  float c_hi = mrb_float(hi);

  float result = cf_clamp(c_a, c_lo, c_hi);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp01(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  float c_a = mrb_float(a);

  float result = cf_clamp01(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp01_int(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  int result = cf_clamp01_int(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_clamp01_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_clamp01_v2(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Aabb c_a = mrb_cptr(a);
  CF_Aabb c_b = mrb_cptr(b);

  CF_Aabb result = cf_clamp_aabb(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp_aabb_v2(mrb_state *mrb, mrb_value self) {
  mrb_value bb, p;

  mrb_get_args(mrb, "oo", &bb, &p);

  CF_Aabb c_bb = mrb_cptr(bb);
  CF_V2 c_p = mrb_cptr(p);

  CF_V2 result = cf_clamp_aabb_v2(c_bb, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_clamp_int(mrb_state *mrb, mrb_value self) {
  mrb_value a, lo, hi;

  mrb_get_args(mrb, "ooo", &a, &lo, &hi);

  int c_a = mrb_fixnum(a);
  int c_lo = mrb_fixnum(lo);
  int c_hi = mrb_fixnum(hi);

  int result = cf_clamp_int(c_a, c_lo, c_hi);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_clamp_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, lo, hi;

  mrb_get_args(mrb, "ooo", &a, &lo, &hi);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_lo = mrb_cptr(lo);
  CF_V2 c_hi = mrb_cptr(hi);

  CF_V2 result = cf_clamp_v2(c_a, c_lo, c_hi);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_collide(mrb_state *mrb, mrb_value self) {
  mrb_value A, ax, typeA, B, bx, typeB, m;

  mrb_get_args(mrb, "ooooooo", &A, &ax, &typeA, &B, &bx, &typeB, &m);

  const void* c_A = mrb_cptr(A);
  const CF_Transform* c_ax = mrb_cptr(ax);
  CF_ShapeType c_typeA = mrb_cptr(typeA);
  const void* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);
  CF_ShapeType c_typeB = mrb_cptr(typeB);
  CF_Manifold* c_m = mrb_cptr(m);

  cf_collide(c_A, c_ax, c_typeA, c_B, c_bx, c_typeB, c_m);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_collide_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Aabb c_a = mrb_cptr(a);
  CF_Aabb c_b = mrb_cptr(b);

  int result = cf_collide_aabb(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_collided(mrb_state *mrb, mrb_value self) {
  mrb_value A, ax, typeA, B, bx, typeB;

  mrb_get_args(mrb, "oooooo", &A, &ax, &typeA, &B, &bx, &typeB);

  const void* c_A = mrb_cptr(A);
  const CF_Transform* c_ax = mrb_cptr(ax);
  CF_ShapeType c_typeA = mrb_cptr(typeA);
  const void* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);
  CF_ShapeType c_typeB = mrb_cptr(typeB);

  int result = cf_collided(c_A, c_ax, c_typeA, c_B, c_bx, c_typeB);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_combine(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Aabb c_a = mrb_cptr(a);
  CF_Aabb c_b = mrb_cptr(b);

  CF_Aabb result = cf_combine(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_contains_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Aabb c_a = mrb_cptr(a);
  CF_Aabb c_b = mrb_cptr(b);

  bool result = cf_contains_aabb(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_contains_point(mrb_state *mrb, mrb_value self) {
  mrb_value bb, p;

  mrb_get_args(mrb, "oo", &bb, &p);

  CF_Aabb c_bb = mrb_cptr(bb);
  CF_V2 c_p = mrb_cptr(p);

  bool result = cf_contains_point(c_bb, c_p);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_cross(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  float result = cf_cross(c_a, c_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cross_f_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  float c_a = mrb_float(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_cross_f_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cross_v2_f(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  float c_b = mrb_float(b);

  CF_V2 result = cf_cross_v2_f(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cube_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_cube_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cube_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_cube_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cube_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_cube_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_cw90(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_cw90(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_det2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  float result = cf_det2(c_a, c_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_distance(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  float result = cf_distance(c_a, c_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_distance_hs(mrb_state *mrb, mrb_value self) {
  mrb_value h, p;

  mrb_get_args(mrb, "oo", &h, &p);

  CF_Halfspace c_h = mrb_cptr(h);
  CF_V2 c_p = mrb_cptr(p);

  float result = cf_distance_hs(c_h, c_p);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_distance_sq(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, p;

  mrb_get_args(mrb, "ooo", &a, &b, &p);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  CF_V2 c_p = mrb_cptr(p);

  float result = cf_distance_sq(c_a, c_b, c_p);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_div_v2_f(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  float c_b = mrb_float(b);

  CF_V2 result = cf_div_v2_f(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_dot(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  float result = cf_dot(c_a, c_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_endpoint(mrb_state *mrb, mrb_value self) {
  mrb_value r;

  mrb_get_args(mrb, "o", &r);

  CF_Ray c_r = mrb_cptr(r);

  CF_V2 result = cf_endpoint(c_r);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_expand_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value aabb, v;

  mrb_get_args(mrb, "oo", &aabb, &v);

  CF_Aabb c_aabb = mrb_cptr(aabb);
  CF_V2 c_v = mrb_cptr(v);

  CF_Aabb result = cf_expand_aabb(c_aabb, c_v);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_expand_aabb_f(mrb_state *mrb, mrb_value self) {
  mrb_value aabb, v;

  mrb_get_args(mrb, "oo", &aabb, &v);

  CF_Aabb c_aabb = mrb_cptr(aabb);
  float c_v = mrb_float(v);

  CF_Aabb result = cf_expand_aabb_f(c_aabb, c_v);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_extents(mrb_state *mrb, mrb_value self) {
  mrb_value aabb;

  mrb_get_args(mrb, "o", &aabb);

  CF_Aabb c_aabb = mrb_cptr(aabb);

  CF_V2 result = cf_extents(c_aabb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_fit_power_of_two(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  int result = cf_fit_power_of_two(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_floor(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_floor(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_fract(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_fract(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_from_angle(mrb_state *mrb, mrb_value self) {
  mrb_value radians;

  mrb_get_args(mrb, "o", &radians);

  float c_radians = mrb_float(radians);

  CF_V2 result = cf_from_angle(c_radians);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_gjk(mrb_state *mrb, mrb_value self) {
  mrb_value A, typeA, ax_ptr, B, typeB, bx_ptr, outA, outB, use_radius, iterations, cache;

  mrb_get_args(mrb, "ooooooooooo", &A, &typeA, &ax_ptr, &B, &typeB, &bx_ptr, &outA, &outB, &use_radius, &iterations, &cache);

  const void* c_A = mrb_cptr(A);
  CF_ShapeType c_typeA = mrb_cptr(typeA);
  const CF_Transform* c_ax_ptr = mrb_cptr(ax_ptr);
  const void* c_B = mrb_cptr(B);
  CF_ShapeType c_typeB = mrb_cptr(typeB);
  const CF_Transform* c_bx_ptr = mrb_cptr(bx_ptr);
  CF_V2* c_outA = mrb_cptr(outA);
  CF_V2* c_outB = mrb_cptr(outB);
  bool c_use_radius = mrb_bool(use_radius);
  int* c_iterations = mrb_cptr(iterations);
  CF_GjkCache* c_cache = mrb_cptr(cache);

  float result = cf_gjk(c_A, c_typeA, c_ax_ptr, c_B, c_typeB, c_bx_ptr, c_outA, c_outB, c_use_radius, c_iterations, c_cache);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_greater_equal_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  int result = cf_greater_equal_v2(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_greater_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  int result = cf_greater_v2(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_half_extents(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_half_extents(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_half_height(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_half_height(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_half_width(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_half_width(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_height(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_height(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_hmax(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  float result = cf_hmax(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_hmin(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  float result = cf_hmin(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_hull(mrb_state *mrb, mrb_value self) {
  mrb_value verts, count;

  mrb_get_args(mrb, "oo", &verts, &count);

  CF_V2* c_verts = mrb_cptr(verts);
  int c_count = mrb_fixnum(count);

  int result = cf_hull(c_verts, c_count);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_impact(mrb_state *mrb, mrb_value self) {
  mrb_value r, t;

  mrb_get_args(mrb, "oo", &r, &t);

  CF_Ray c_r = mrb_cptr(r);
  float c_t = mrb_float(t);

  CF_V2 result = cf_impact(c_r, c_t);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_inflate(mrb_state *mrb, mrb_value self) {
  mrb_value shape, type, skin_factor;

  mrb_get_args(mrb, "ooo", &shape, &type, &skin_factor);

  void* c_shape = mrb_cptr(shape);
  CF_ShapeType c_type = mrb_cptr(type);
  float c_skin_factor = mrb_float(skin_factor);

  cf_inflate(c_shape, c_type, c_skin_factor);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_intersect(mrb_state *mrb, mrb_value self) {
  mrb_value da, db;

  mrb_get_args(mrb, "oo", &da, &db);

  float c_da = mrb_float(da);
  float c_db = mrb_float(db);

  float result = cf_intersect(c_da, c_db);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_intersect_halfspace(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, da, db;

  mrb_get_args(mrb, "oooo", &a, &b, &da, &db);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  float c_da = mrb_float(da);
  float c_db = mrb_float(db);

  CF_V2 result = cf_intersect_halfspace(c_a, c_b, c_da, c_db);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_intersect_halfspace2(mrb_state *mrb, mrb_value self) {
  mrb_value h, a, b;

  mrb_get_args(mrb, "ooo", &h, &a, &b);

  CF_Halfspace c_h = mrb_cptr(h);
  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_intersect_halfspace2(c_h, c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_intersect_halfspace3(mrb_state *mrb, mrb_value self) {
  mrb_value ha, hb;

  mrb_get_args(mrb, "oo", &ha, &hb);

  CF_Halfspace c_ha = mrb_cptr(ha);
  CF_Halfspace c_hb = mrb_cptr(hb);

  CF_V2 result = cf_intersect_halfspace3(c_ha, c_hb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_invert(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_M3x2 c_a = mrb_cptr(a);

  CF_M3x2 result = cf_invert(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_is_even(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  int c_x = mrb_fixnum(x);

  bool result = cf_is_even(c_x);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_is_odd(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  int c_x = mrb_fixnum(x);

  bool result = cf_is_odd(c_x);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_is_power_of_two(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  bool result = cf_is_power_of_two(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_is_power_of_two_uint(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  uint64_t c_a = mrb_fixnum(a);

  bool result = cf_is_power_of_two_uint(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_left(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_left(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_len(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  float result = cf_len(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_len_sq(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  float result = cf_len_sq(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_lerp(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, t;

  mrb_get_args(mrb, "ooo", &a, &b, &t);

  float c_a = mrb_float(a);
  float c_b = mrb_float(b);
  float c_t = mrb_float(t);

  float result = cf_lerp(c_a, c_b, c_t);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_lerp_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, t;

  mrb_get_args(mrb, "ooo", &a, &b, &t);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  float c_t = mrb_float(t);

  CF_V2 result = cf_lerp_v2(c_a, c_b, c_t);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_lesser_equal_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  int result = cf_lesser_equal_v2(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_lesser_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  int result = cf_lesser_v2(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_make_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value min, max;

  mrb_get_args(mrb, "oo", &min, &max);

  CF_V2 c_min = mrb_cptr(min);
  CF_V2 c_max = mrb_cptr(max);

  CF_Aabb result = cf_make_aabb(c_min, c_max);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_aabb_center_half_extents(mrb_state *mrb, mrb_value self) {
  mrb_value center, half_extents;

  mrb_get_args(mrb, "oo", &center, &half_extents);

  CF_V2 c_center = mrb_cptr(center);
  CF_V2 c_half_extents = mrb_cptr(half_extents);

  CF_Aabb result = cf_make_aabb_center_half_extents(c_center, c_half_extents);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_aabb_from_top_left(mrb_state *mrb, mrb_value self) {
  mrb_value top_left, w, h;

  mrb_get_args(mrb, "ooo", &top_left, &w, &h);

  CF_V2 c_top_left = mrb_cptr(top_left);
  float c_w = mrb_float(w);
  float c_h = mrb_float(h);

  CF_Aabb result = cf_make_aabb_from_top_left(c_top_left, c_w, c_h);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_aabb_pos_w_h(mrb_state *mrb, mrb_value self) {
  mrb_value pos, w, h;

  mrb_get_args(mrb, "ooo", &pos, &w, &h);

  CF_V2 c_pos = mrb_cptr(pos);
  float c_w = mrb_float(w);
  float c_h = mrb_float(h);

  CF_Aabb result = cf_make_aabb_pos_w_h(c_pos, c_w, c_h);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_aabb_verts(mrb_state *mrb, mrb_value self) {
  mrb_value verts, count;

  mrb_get_args(mrb, "oo", &verts, &count);

  CF_V2* c_verts = mrb_cptr(verts);
  int c_count = mrb_fixnum(count);

  CF_Aabb result = cf_make_aabb_verts(c_verts, c_count);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_capsule(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, radius;

  mrb_get_args(mrb, "ooo", &a, &b, &radius);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  float c_radius = mrb_float(radius);

  CF_Capsule result = cf_make_capsule(c_a, c_b, c_radius);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_capsule2(mrb_state *mrb, mrb_value self) {
  mrb_value p, height, radius;

  mrb_get_args(mrb, "ooo", &p, &height, &radius);

  CF_V2 c_p = mrb_cptr(p);
  float c_height = mrb_float(height);
  float c_radius = mrb_float(radius);

  CF_Capsule result = cf_make_capsule2(c_p, c_height, c_radius);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_circle(mrb_state *mrb, mrb_value self) {
  mrb_value pos, radius;

  mrb_get_args(mrb, "oo", &pos, &radius);

  CF_V2 c_pos = mrb_cptr(pos);
  float c_radius = mrb_float(radius);

  CF_Circle result = cf_make_circle(c_pos, c_radius);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_identity(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_M3x2 result = cf_make_identity();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_poly(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_Poly* c_p = mrb_cptr(p);

  cf_make_poly(c_p);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_make_ray(mrb_state *mrb, mrb_value self) {
  mrb_value start, direction_normalized, length;

  mrb_get_args(mrb, "ooo", &start, &direction_normalized, &length);

  CF_V2 c_start = mrb_cptr(start);
  CF_V2 c_direction_normalized = mrb_cptr(direction_normalized);
  float c_length = mrb_float(length);

  CF_Ray result = cf_make_ray(c_start, c_direction_normalized, c_length);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_rotation(mrb_state *mrb, mrb_value self) {
  mrb_value radians;

  mrb_get_args(mrb, "o", &radians);

  float c_radians = mrb_float(radians);

  CF_M3x2 result = cf_make_rotation(c_radians);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_scale(mrb_state *mrb, mrb_value self) {
  mrb_value s;

  mrb_get_args(mrb, "o", &s);

  CF_V2 c_s = mrb_cptr(s);

  CF_M3x2 result = cf_make_scale(c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_scale_f(mrb_state *mrb, mrb_value self) {
  mrb_value s;

  mrb_get_args(mrb, "o", &s);

  float c_s = mrb_float(s);

  CF_M3x2 result = cf_make_scale_f(c_s);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_scale_translation(mrb_state *mrb, mrb_value self) {
  mrb_value s, p;

  mrb_get_args(mrb, "oo", &s, &p);

  CF_V2 c_s = mrb_cptr(s);
  CF_V2 c_p = mrb_cptr(p);

  CF_M3x2 result = cf_make_scale_translation(c_s, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_scale_translation_f(mrb_state *mrb, mrb_value self) {
  mrb_value s, p;

  mrb_get_args(mrb, "oo", &s, &p);

  float c_s = mrb_float(s);
  CF_V2 c_p = mrb_cptr(p);

  CF_M3x2 result = cf_make_scale_translation_f(c_s, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_scale_translation_f_f(mrb_state *mrb, mrb_value self) {
  mrb_value sx, sy, p;

  mrb_get_args(mrb, "ooo", &sx, &sy, &p);

  float c_sx = mrb_float(sx);
  float c_sy = mrb_float(sy);
  CF_V2 c_p = mrb_cptr(p);

  CF_M3x2 result = cf_make_scale_translation_f_f(c_sx, c_sy, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_transform(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_Transform result = cf_make_transform();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_transform_TR(mrb_state *mrb, mrb_value self) {
  mrb_value p, radians;

  mrb_get_args(mrb, "oo", &p, &radians);

  CF_V2 c_p = mrb_cptr(p);
  float c_radians = mrb_float(radians);

  CF_Transform result = cf_make_transform_TR(c_p, c_radians);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_transform_TSR(mrb_state *mrb, mrb_value self) {
  mrb_value p, s, radians;

  mrb_get_args(mrb, "ooo", &p, &s, &radians);

  CF_V2 c_p = mrb_cptr(p);
  CF_V2 c_s = mrb_cptr(s);
  float c_radians = mrb_float(radians);

  CF_M3x2 result = cf_make_transform_TSR(c_p, c_s, c_radians);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_translation(mrb_state *mrb, mrb_value self) {
  mrb_value p;

  mrb_get_args(mrb, "o", &p);

  CF_V2 c_p = mrb_cptr(p);

  CF_M3x2 result = cf_make_translation(c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_make_translation_f(mrb_state *mrb, mrb_value self) {
  mrb_value x, y;

  mrb_get_args(mrb, "oo", &x, &y);

  float c_x = mrb_float(x);
  float c_y = mrb_float(y);

  CF_M3x2 result = cf_make_translation_f(c_x, c_y);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_max_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_max_aabb(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_max_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_max_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_midpoint(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_midpoint(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_min_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_min_aabb(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_min_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_min_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mod(mrb_state *mrb, mrb_value self) {
  mrb_value x, m;

  mrb_get_args(mrb, "oo", &x, &m);

  float c_x = mrb_float(x);
  float c_m = mrb_float(m);

  float result = cf_mod(c_x, c_m);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mulT_sc(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_SinCos c_a = mrb_cptr(a);
  CF_SinCos c_b = mrb_cptr(b);

  CF_SinCos result = cf_mulT_sc(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mulT_sc_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_SinCos c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mulT_sc_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mulT_tf(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_Transform c_b = mrb_cptr(b);

  CF_Transform result = cf_mulT_tf(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mulT_tf_hs(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_Halfspace c_b = mrb_cptr(b);

  CF_Halfspace result = cf_mulT_tf_hs(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mulT_tf_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mulT_tf_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_m2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_M2x2 c_a = mrb_cptr(a);
  CF_M2x2 c_b = mrb_cptr(b);

  CF_M2x2 result = cf_mul_m2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_m2_f(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_M2x2 c_a = mrb_cptr(a);
  float c_b = mrb_float(b);

  CF_M2x2 result = cf_mul_m2_f(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_m2_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_M2x2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mul_m2_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_m32(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_M3x2 c_a = mrb_cptr(a);
  CF_M3x2 c_b = mrb_cptr(b);

  CF_M3x2 result = cf_mul_m32(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_m32_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_M3x2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mul_m32_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_sc(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_SinCos c_a = mrb_cptr(a);
  CF_SinCos c_b = mrb_cptr(b);

  CF_SinCos result = cf_mul_sc(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_sc_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_SinCos c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mul_sc_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_tf(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_Transform c_b = mrb_cptr(b);

  CF_Transform result = cf_mul_tf(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_tf_circle(mrb_state *mrb, mrb_value self) {
  mrb_value tx, a;

  mrb_get_args(mrb, "oo", &tx, &a);

  CF_Transform c_tx = mrb_cptr(tx);
  CF_Circle c_a = mrb_cptr(a);

  CF_Circle result = cf_mul_tf_circle(c_tx, c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_tf_hs(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_Halfspace c_b = mrb_cptr(b);

  CF_Halfspace result = cf_mul_tf_hs(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_tf_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Transform c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mul_tf_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_mul_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_mul_v2_f(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  float c_b = mrb_float(b);

  CF_V2 result = cf_mul_v2_f(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_neg_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_neg_v2(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_norm(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_norm(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_norms(mrb_state *mrb, mrb_value self) {
  mrb_value verts, norms, count;

  mrb_get_args(mrb, "ooo", &verts, &norms, &count);

  CF_V2* c_verts = mrb_cptr(verts);
  CF_V2* c_norms = mrb_cptr(norms);
  int c_count = mrb_fixnum(count);

  cf_norms(c_verts, c_norms, c_count);
  return mrb_nil_value();
}
/*  */
static mrb_value mrb_cf_origin(mrb_state *mrb, mrb_value self) {
  mrb_value h;

  mrb_get_args(mrb, "o", &h);

  CF_Halfspace c_h = mrb_cptr(h);

  CF_V2 result = cf_origin(c_h);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ortho_2d(mrb_state *mrb, mrb_value self) {
  mrb_value x, y, scale_x, scale_y;

  mrb_get_args(mrb, "oooo", &x, &y, &scale_x, &scale_y);

  float c_x = mrb_float(x);
  float c_y = mrb_float(y);
  float c_scale_x = mrb_float(scale_x);
  float c_scale_y = mrb_float(scale_y);

  CF_M3x2 result = cf_ortho_2d(c_x, c_y, c_scale_x, c_scale_y);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_overlaps(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_Aabb c_a = mrb_cptr(a);
  CF_Aabb c_b = mrb_cptr(b);

  int result = cf_overlaps(c_a, c_b);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_parallel(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, tol;

  mrb_get_args(mrb, "ooo", &a, &b, &tol);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  float c_tol = mrb_float(tol);

  bool result = cf_parallel(c_a, c_b, c_tol);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_parallel2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b, c, tol;

  mrb_get_args(mrb, "oooo", &a, &b, &c, &tol);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);
  CF_V2 c_c = mrb_cptr(c);
  float c_tol = mrb_float(tol);

  bool result = cf_parallel2(c_a, c_b, c_c, c_tol);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_perp(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_perp(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_plane(mrb_state *mrb, mrb_value self) {
  mrb_value n, d;

  mrb_get_args(mrb, "oo", &n, &d);

  CF_V2 c_n = mrb_cptr(n);
  float c_d = mrb_float(d);

  CF_Halfspace result = cf_plane(c_n, c_d);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_plane2(mrb_state *mrb, mrb_value self) {
  mrb_value n, p;

  mrb_get_args(mrb, "oo", &n, &p);

  CF_V2 c_n = mrb_cptr(n);
  CF_V2 c_p = mrb_cptr(p);

  CF_Halfspace result = cf_plane2(c_n, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_poly_to_poly(mrb_state *mrb, mrb_value self) {
  mrb_value A, ax, B, bx;

  mrb_get_args(mrb, "oooo", &A, &ax, &B, &bx);

  const CF_Poly* c_A = mrb_cptr(A);
  const CF_Transform* c_ax = mrb_cptr(ax);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  bool result = cf_poly_to_poly(c_A, c_ax, c_B, c_bx);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_poly_to_poly_manifold(mrb_state *mrb, mrb_value self) {
  mrb_value A, ax, B, bx;

  mrb_get_args(mrb, "oooo", &A, &ax, &B, &bx);

  const CF_Poly* c_A = mrb_cptr(A);
  const CF_Transform* c_ax = mrb_cptr(ax);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx = mrb_cptr(bx);

  CF_Manifold result = cf_poly_to_poly_manifold(c_A, c_ax, c_B, c_bx);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_project(mrb_state *mrb, mrb_value self) {
  mrb_value h, p;

  mrb_get_args(mrb, "oo", &h, &p);

  CF_Halfspace c_h = mrb_cptr(h);
  CF_V2 c_p = mrb_cptr(p);

  CF_V2 result = cf_project(c_h, c_p);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quad_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quad_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quad_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quad_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quad_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quad_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quart_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quart_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quart_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quart_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quart_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quart_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quint_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quint_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quint_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quint_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_quint_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_quint_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ray_to_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Ray c_A = mrb_cptr(A);
  CF_Aabb c_B = mrb_cptr(B);

  CF_Raycast result = cf_ray_to_aabb(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ray_to_capsule(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Ray c_A = mrb_cptr(A);
  CF_Capsule c_B = mrb_cptr(B);

  CF_Raycast result = cf_ray_to_capsule(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ray_to_circle(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Ray c_A = mrb_cptr(A);
  CF_Circle c_B = mrb_cptr(B);

  CF_Raycast result = cf_ray_to_circle(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ray_to_halfspace(mrb_state *mrb, mrb_value self) {
  mrb_value A, B;

  mrb_get_args(mrb, "oo", &A, &B);

  CF_Ray c_A = mrb_cptr(A);
  CF_Halfspace c_B = mrb_cptr(B);

  CF_Raycast result = cf_ray_to_halfspace(c_A, c_B);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_ray_to_poly(mrb_state *mrb, mrb_value self) {
  mrb_value A, B, bx_ptr;

  mrb_get_args(mrb, "ooo", &A, &B, &bx_ptr);

  CF_Ray c_A = mrb_cptr(A);
  const CF_Poly* c_B = mrb_cptr(B);
  const CF_Transform* c_bx_ptr = mrb_cptr(bx_ptr);

  CF_Raycast result = cf_ray_to_poly(c_A, c_B, c_bx_ptr);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_reflect_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, n;

  mrb_get_args(mrb, "oo", &a, &n);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_n = mrb_cptr(n);

  CF_V2 result = cf_reflect_v2(c_a, c_n);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_remap(mrb_state *mrb, mrb_value self) {
  mrb_value t, old_lo, old_hi, lo, hi;

  mrb_get_args(mrb, "ooooo", &t, &old_lo, &old_hi, &lo, &hi);

  float c_t = mrb_float(t);
  float c_old_lo = mrb_float(old_lo);
  float c_old_hi = mrb_float(old_hi);
  float c_lo = mrb_float(lo);
  float c_hi = mrb_float(hi);

  float result = cf_remap(c_t, c_old_lo, c_old_hi, c_lo, c_hi);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_remap01(mrb_state *mrb, mrb_value self) {
  mrb_value t, lo, hi;

  mrb_get_args(mrb, "ooo", &t, &lo, &hi);

  float c_t = mrb_float(t);
  float c_lo = mrb_float(lo);
  float c_hi = mrb_float(hi);

  float result = cf_remap01(c_t, c_lo, c_hi);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_right(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_right(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_round(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_round(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_safe_invert(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  float c_a = mrb_float(a);

  float result = cf_safe_invert(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_safe_invert_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_safe_invert_v2(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_safe_norm(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_safe_norm(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_safe_norm_f(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  float c_a = mrb_float(a);

  float result = cf_safe_norm_f(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_safe_norm_int(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  int result = cf_safe_norm_int(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_shift(mrb_state *mrb, mrb_value self) {
  mrb_value h, d;

  mrb_get_args(mrb, "oo", &h, &d);

  CF_Halfspace c_h = mrb_cptr(h);
  float c_d = mrb_float(d);

  CF_Halfspace result = cf_shift(c_h, c_d);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_shortest_arc(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  float result = cf_shortest_arc(c_a, c_b);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sign(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  float c_a = mrb_float(a);

  float result = cf_sign(c_a);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sign_int(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  int c_a = mrb_fixnum(a);

  int result = cf_sign_int(c_a);
  return mrb_fixnum_value(result);
}
/*  */
static mrb_value mrb_cf_sign_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_sign_v2(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sin_in(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_sin_in(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sin_in_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_sin_in_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sin_out(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_sin_out(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sincos(mrb_state *mrb, mrb_value self) {
  // No parameters
  CF_SinCos result = cf_sincos();
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sincos_f(mrb_state *mrb, mrb_value self) {
  mrb_value radians;

  mrb_get_args(mrb, "o", &radians);

  float c_radians = mrb_float(radians);

  CF_SinCos result = cf_sincos_f(c_radians);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_skew(mrb_state *mrb, mrb_value self) {
  mrb_value a;

  mrb_get_args(mrb, "o", &a);

  CF_V2 c_a = mrb_cptr(a);

  CF_V2 result = cf_skew(c_a);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_slice(mrb_state *mrb, mrb_value self) {
  mrb_value slice_plane, slice_me, k_epsilon;

  mrb_get_args(mrb, "ooo", &slice_plane, &slice_me, &k_epsilon);

  CF_Halfspace c_slice_plane = mrb_cptr(slice_plane);
  CF_Poly c_slice_me = mrb_cptr(slice_me);
  const float c_k_epsilon = mrb_fixnum(k_epsilon) /* TODO: Unknown type `const float' */;

  CF_SliceOutput result = cf_slice(c_slice_plane, c_slice_me, c_k_epsilon);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_smoothstep(mrb_state *mrb, mrb_value self) {
  mrb_value x;

  mrb_get_args(mrb, "o", &x);

  float c_x = mrb_float(x);

  float result = cf_smoothstep(c_x);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_sub_v2(mrb_state *mrb, mrb_value self) {
  mrb_value a, b;

  mrb_get_args(mrb, "oo", &a, &b);

  CF_V2 c_a = mrb_cptr(a);
  CF_V2 c_b = mrb_cptr(b);

  CF_V2 result = cf_sub_v2(c_a, c_b);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_surface_area_aabb(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_surface_area_aabb(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_surface_area_circle(mrb_state *mrb, mrb_value self) {
  mrb_value c;

  mrb_get_args(mrb, "o", &c);

  CF_Circle c_c = mrb_cptr(c);

  float result = cf_surface_area_circle(c_c);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_toi(mrb_state *mrb, mrb_value self) {
  mrb_value A, typeA, ax_ptr, vA, B, typeB, bx_ptr, vB, use_radius;

  mrb_get_args(mrb, "ooooooooo", &A, &typeA, &ax_ptr, &vA, &B, &typeB, &bx_ptr, &vB, &use_radius);

  const void* c_A = mrb_cptr(A);
  CF_ShapeType c_typeA = mrb_cptr(typeA);
  const CF_Transform* c_ax_ptr = mrb_cptr(ax_ptr);
  CF_V2 c_vA = mrb_cptr(vA);
  const void* c_B = mrb_cptr(B);
  CF_ShapeType c_typeB = mrb_cptr(typeB);
  const CF_Transform* c_bx_ptr = mrb_cptr(bx_ptr);
  CF_V2 c_vB = mrb_cptr(vB);
  int c_use_radius = mrb_fixnum(use_radius);

  CF_ToiResult result = cf_toi(c_A, c_typeA, c_ax_ptr, c_vA, c_B, c_typeB, c_bx_ptr, c_vB, c_use_radius);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_top(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_top(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_top_left(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_top_left(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_top_right(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  CF_V2 result = cf_top_right(c_bb);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_v2(mrb_state *mrb, mrb_value self) {
  mrb_value x, y;

  mrb_get_args(mrb, "oo", &x, &y);

  float c_x = mrb_float(x);
  float c_y = mrb_float(y);

  CF_V2 result = cf_v2(c_x, c_y);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_width(mrb_state *mrb, mrb_value self) {
  mrb_value bb;

  mrb_get_args(mrb, "o", &bb);

  CF_Aabb c_bb = mrb_cptr(bb);

  float result = cf_width(c_bb);
  return mrb_float_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_x_axis(mrb_state *mrb, mrb_value self) {
  mrb_value r;

  mrb_get_args(mrb, "o", &r);

  CF_SinCos c_r = mrb_cptr(r);

  CF_V2 result = cf_x_axis(c_r);
  return mrb_cptr_value(mrb, result);
}
/*  */
static mrb_value mrb_cf_y_axis(mrb_state *mrb, mrb_value self) {
  mrb_value r;

  mrb_get_args(mrb, "o", &r);

  CF_SinCos c_r = mrb_cptr(r);

  CF_V2 result = cf_y_axis(c_r);
  return mrb_cptr_value(mrb, result);
}
CF_V2* mrb_cf_v2_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_v2_data_t* data = (mrb_cf_v2_data_t*) DATA_PTR(self);
    return data->cf_v2_ptr;
}

CF_SinCos* mrb_cf_sincos_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_sincos_data_t* data = (mrb_cf_sincos_data_t*) DATA_PTR(self);
    return data->cf_sincos_ptr;
}

CF_M2x2* mrb_cf_m2x2_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_m2x2_data_t* data = (mrb_cf_m2x2_data_t*) DATA_PTR(self);
    return data->cf_m2x2_ptr;
}

CF_M3x2* mrb_cf_m3x2_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_m3x2_data_t* data = (mrb_cf_m3x2_data_t*) DATA_PTR(self);
    return data->cf_m3x2_ptr;
}

CF_Transform* mrb_cf_transform_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_transform_data_t* data = (mrb_cf_transform_data_t*) DATA_PTR(self);
    return data->cf_transform_ptr;
}

CF_Halfspace* mrb_cf_halfspace_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_halfspace_data_t* data = (mrb_cf_halfspace_data_t*) DATA_PTR(self);
    return data->cf_halfspace_ptr;
}

CF_Ray* mrb_cf_ray_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_ray_data_t* data = (mrb_cf_ray_data_t*) DATA_PTR(self);
    return data->cf_ray_ptr;
}

CF_Raycast* mrb_cf_raycast_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_raycast_data_t* data = (mrb_cf_raycast_data_t*) DATA_PTR(self);
    return data->cf_raycast_ptr;
}

CF_Circle* mrb_cf_circle_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_circle_data_t* data = (mrb_cf_circle_data_t*) DATA_PTR(self);
    return data->cf_circle_ptr;
}

CF_Aabb* mrb_cf_aabb_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_aabb_data_t* data = (mrb_cf_aabb_data_t*) DATA_PTR(self);
    return data->cf_aabb_ptr;
}

CF_Rect* mrb_cf_rect_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_rect_data_t* data = (mrb_cf_rect_data_t*) DATA_PTR(self);
    return data->cf_rect_ptr;
}

CF_Poly* mrb_cf_poly_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_poly_data_t* data = (mrb_cf_poly_data_t*) DATA_PTR(self);
    return data->cf_poly_ptr;
}

CF_Capsule* mrb_cf_capsule_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_capsule_data_t* data = (mrb_cf_capsule_data_t*) DATA_PTR(self);
    return data->cf_capsule_ptr;
}

CF_Manifold* mrb_cf_manifold_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_manifold_data_t* data = (mrb_cf_manifold_data_t*) DATA_PTR(self);
    return data->cf_manifold_ptr;
}

CF_SliceOutput* mrb_cf_sliceoutput_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_sliceoutput_data_t* data = (mrb_cf_sliceoutput_data_t*) DATA_PTR(self);
    return data->cf_sliceoutput_ptr;
}

CF_GjkCache* mrb_cf_gjkcache_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_gjkcache_data_t* data = (mrb_cf_gjkcache_data_t*) DATA_PTR(self);
    return data->cf_gjkcache_ptr;
}

CF_ToiResult* mrb_cf_toiresult_get_ptr(mrb_state* mrb, mrb_value self)
{
    mrb_cf_toiresult_data_t* data = (mrb_cf_toiresult_data_t*) DATA_PTR(self);
    return data->cf_toiresult_ptr;
}


/**
 * Initialize the module
 */
void mrb_mruby_cute_cute_math_gem_init(mrb_state *mrb, struct RClass *mCute)
{
  // Define enums
  

  // Define enum def definitions
  #define CF_ENUM(K, V) mrb_define_const(mrb, mCute, "CF_"#K, mrb_fixnum_value(V));
  CF_SHAPE_TYPE_DEFS
  #undef CF_ENUM

  // Define functions
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_aabb", mrb_cf_aabb_to_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_aabb_manifold", mrb_cf_aabb_to_aabb_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_capsule", mrb_cf_aabb_to_capsule, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_capsule_manifold", mrb_cf_aabb_to_capsule_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_poly", mrb_cf_aabb_to_poly, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_aabb_to_poly_manifold", mrb_cf_aabb_to_poly_manifold, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_aabb_verts", mrb_cf_aabb_verts, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_abs", mrb_cf_abs, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_abs_int", mrb_cf_abs_int, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_abs_v2", mrb_cf_abs_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_add_v2", mrb_cf_add_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_angle_diff", mrb_cf_angle_diff, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_area_aabb", mrb_cf_area_aabb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_area_circle", mrb_cf_area_circle, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_atan2_360", mrb_cf_atan2_360, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_atan2_360_sc", mrb_cf_atan2_360_sc, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_atan2_360_v2", mrb_cf_atan2_360_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_back_in", mrb_cf_back_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_back_in_out", mrb_cf_back_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_back_out", mrb_cf_back_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_bezier", mrb_cf_bezier, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_bezier2", mrb_cf_bezier2, MRB_ARGS_REQ(5));
  mrb_define_module_function(mrb, mCute, "cf_bottom", mrb_cf_bottom, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_bottom_left", mrb_cf_bottom_left, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_bottom_right", mrb_cf_bottom_right, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_calc_area", mrb_cf_calc_area, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_capsule_to_capsule", mrb_cf_capsule_to_capsule, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_capsule_to_capsule_manifold", mrb_cf_capsule_to_capsule_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_capsule_to_poly", mrb_cf_capsule_to_poly, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_capsule_to_poly_manifold", mrb_cf_capsule_to_poly_manifold, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_cast_ray", mrb_cf_cast_ray, MRB_ARGS_REQ(5));
  mrb_define_module_function(mrb, mCute, "cf_ceil", mrb_cf_ceil, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_center", mrb_cf_center, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_center_of_mass", mrb_cf_center_of_mass, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_centroid", mrb_cf_centroid, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_in", mrb_cf_circle_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_circle_in_out", mrb_cf_circle_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_circle_out", mrb_cf_circle_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_aabb", mrb_cf_circle_to_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_aabb_manifold", mrb_cf_circle_to_aabb_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_capsule", mrb_cf_circle_to_capsule, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_capsule_manifold", mrb_cf_circle_to_capsule_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_circle", mrb_cf_circle_to_circle, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_circle_manifold", mrb_cf_circle_to_circle_manifold, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_poly", mrb_cf_circle_to_poly, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_circle_to_poly_manifold", mrb_cf_circle_to_poly_manifold, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_clamp", mrb_cf_clamp, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_clamp01", mrb_cf_clamp01, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_clamp01_int", mrb_cf_clamp01_int, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_clamp01_v2", mrb_cf_clamp01_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_clamp_aabb", mrb_cf_clamp_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_clamp_aabb_v2", mrb_cf_clamp_aabb_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_clamp_int", mrb_cf_clamp_int, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_clamp_v2", mrb_cf_clamp_v2, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_collide", mrb_cf_collide, MRB_ARGS_REQ(7));
  mrb_define_module_function(mrb, mCute, "cf_collide_aabb", mrb_cf_collide_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_collided", mrb_cf_collided, MRB_ARGS_REQ(6));
  mrb_define_module_function(mrb, mCute, "cf_combine", mrb_cf_combine, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_contains_aabb", mrb_cf_contains_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_contains_point", mrb_cf_contains_point, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_cross", mrb_cf_cross, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_cross_f_v2", mrb_cf_cross_f_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_cross_v2_f", mrb_cf_cross_v2_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_cube_in", mrb_cf_cube_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_cube_in_out", mrb_cf_cube_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_cube_out", mrb_cf_cube_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_cw90", mrb_cf_cw90, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_det2", mrb_cf_det2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_distance", mrb_cf_distance, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_distance_hs", mrb_cf_distance_hs, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_distance_sq", mrb_cf_distance_sq, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_div_v2_f", mrb_cf_div_v2_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_dot", mrb_cf_dot, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_endpoint", mrb_cf_endpoint, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_expand_aabb", mrb_cf_expand_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_expand_aabb_f", mrb_cf_expand_aabb_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_extents", mrb_cf_extents, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_fit_power_of_two", mrb_cf_fit_power_of_two, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_floor", mrb_cf_floor, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_fract", mrb_cf_fract, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_from_angle", mrb_cf_from_angle, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_gjk", mrb_cf_gjk, MRB_ARGS_REQ(11));
  mrb_define_module_function(mrb, mCute, "cf_greater_equal_v2", mrb_cf_greater_equal_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_greater_v2", mrb_cf_greater_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_half_extents", mrb_cf_half_extents, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_half_height", mrb_cf_half_height, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_half_width", mrb_cf_half_width, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_height", mrb_cf_height, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_hmax", mrb_cf_hmax, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_hmin", mrb_cf_hmin, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_hull", mrb_cf_hull, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_impact", mrb_cf_impact, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_inflate", mrb_cf_inflate, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_intersect", mrb_cf_intersect, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_intersect_halfspace", mrb_cf_intersect_halfspace, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_intersect_halfspace2", mrb_cf_intersect_halfspace2, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_intersect_halfspace3", mrb_cf_intersect_halfspace3, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_invert", mrb_cf_invert, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_is_even", mrb_cf_is_even, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_is_odd", mrb_cf_is_odd, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_is_power_of_two", mrb_cf_is_power_of_two, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_is_power_of_two_uint", mrb_cf_is_power_of_two_uint, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_left", mrb_cf_left, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_len", mrb_cf_len, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_len_sq", mrb_cf_len_sq, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_lerp", mrb_cf_lerp, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_lerp_v2", mrb_cf_lerp_v2, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_lesser_equal_v2", mrb_cf_lesser_equal_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_lesser_v2", mrb_cf_lesser_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_aabb", mrb_cf_make_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_aabb_center_half_extents", mrb_cf_make_aabb_center_half_extents, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_aabb_from_top_left", mrb_cf_make_aabb_from_top_left, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_aabb_pos_w_h", mrb_cf_make_aabb_pos_w_h, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_aabb_verts", mrb_cf_make_aabb_verts, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_capsule", mrb_cf_make_capsule, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_capsule2", mrb_cf_make_capsule2, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_circle", mrb_cf_make_circle, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_identity", mrb_cf_make_identity, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_make_poly", mrb_cf_make_poly, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_ray", mrb_cf_make_ray, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_rotation", mrb_cf_make_rotation, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_scale", mrb_cf_make_scale, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_scale_f", mrb_cf_make_scale_f, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_scale_translation", mrb_cf_make_scale_translation, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_scale_translation_f", mrb_cf_make_scale_translation_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_scale_translation_f_f", mrb_cf_make_scale_translation_f_f, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_transform", mrb_cf_make_transform, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_make_transform_TR", mrb_cf_make_transform_TR, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_make_transform_TSR", mrb_cf_make_transform_TSR, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_make_translation", mrb_cf_make_translation, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_make_translation_f", mrb_cf_make_translation_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_max_aabb", mrb_cf_max_aabb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_max_v2", mrb_cf_max_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_midpoint", mrb_cf_midpoint, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_min_aabb", mrb_cf_min_aabb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_min_v2", mrb_cf_min_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mod", mrb_cf_mod, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mulT_sc", mrb_cf_mulT_sc, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mulT_sc_v2", mrb_cf_mulT_sc_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mulT_tf", mrb_cf_mulT_tf, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mulT_tf_hs", mrb_cf_mulT_tf_hs, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mulT_tf_v2", mrb_cf_mulT_tf_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_m2", mrb_cf_mul_m2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_m2_f", mrb_cf_mul_m2_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_m2_v2", mrb_cf_mul_m2_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_m32", mrb_cf_mul_m32, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_m32_v2", mrb_cf_mul_m32_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_sc", mrb_cf_mul_sc, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_sc_v2", mrb_cf_mul_sc_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_tf", mrb_cf_mul_tf, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_tf_circle", mrb_cf_mul_tf_circle, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_tf_hs", mrb_cf_mul_tf_hs, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_tf_v2", mrb_cf_mul_tf_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_v2", mrb_cf_mul_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_mul_v2_f", mrb_cf_mul_v2_f, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_neg_v2", mrb_cf_neg_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_norm", mrb_cf_norm, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_norms", mrb_cf_norms, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_origin", mrb_cf_origin, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_ortho_2d", mrb_cf_ortho_2d, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_overlaps", mrb_cf_overlaps, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_parallel", mrb_cf_parallel, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_parallel2", mrb_cf_parallel2, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_perp", mrb_cf_perp, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_plane", mrb_cf_plane, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_plane2", mrb_cf_plane2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_poly_to_poly", mrb_cf_poly_to_poly, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_poly_to_poly_manifold", mrb_cf_poly_to_poly_manifold, MRB_ARGS_REQ(4));
  mrb_define_module_function(mrb, mCute, "cf_project", mrb_cf_project, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_quad_in", mrb_cf_quad_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quad_in_out", mrb_cf_quad_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quad_out", mrb_cf_quad_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quart_in", mrb_cf_quart_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quart_in_out", mrb_cf_quart_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quart_out", mrb_cf_quart_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quint_in", mrb_cf_quint_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quint_in_out", mrb_cf_quint_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_quint_out", mrb_cf_quint_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_ray_to_aabb", mrb_cf_ray_to_aabb, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_ray_to_capsule", mrb_cf_ray_to_capsule, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_ray_to_circle", mrb_cf_ray_to_circle, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_ray_to_halfspace", mrb_cf_ray_to_halfspace, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_ray_to_poly", mrb_cf_ray_to_poly, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_reflect_v2", mrb_cf_reflect_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_remap", mrb_cf_remap, MRB_ARGS_REQ(5));
  mrb_define_module_function(mrb, mCute, "cf_remap01", mrb_cf_remap01, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_right", mrb_cf_right, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_round", mrb_cf_round, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_safe_invert", mrb_cf_safe_invert, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_safe_invert_v2", mrb_cf_safe_invert_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_safe_norm", mrb_cf_safe_norm, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_safe_norm_f", mrb_cf_safe_norm_f, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_safe_norm_int", mrb_cf_safe_norm_int, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_shift", mrb_cf_shift, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_shortest_arc", mrb_cf_shortest_arc, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_sign", mrb_cf_sign, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sign_int", mrb_cf_sign_int, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sign_v2", mrb_cf_sign_v2, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sin_in", mrb_cf_sin_in, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sin_in_out", mrb_cf_sin_in_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sin_out", mrb_cf_sin_out, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sincos", mrb_cf_sincos, MRB_ARGS_REQ(0));
  mrb_define_module_function(mrb, mCute, "cf_sincos_f", mrb_cf_sincos_f, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_skew", mrb_cf_skew, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_slice", mrb_cf_slice, MRB_ARGS_REQ(3));
  mrb_define_module_function(mrb, mCute, "cf_smoothstep", mrb_cf_smoothstep, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_sub_v2", mrb_cf_sub_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_surface_area_aabb", mrb_cf_surface_area_aabb, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_surface_area_circle", mrb_cf_surface_area_circle, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_toi", mrb_cf_toi, MRB_ARGS_REQ(9));
  mrb_define_module_function(mrb, mCute, "cf_top", mrb_cf_top, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_top_left", mrb_cf_top_left, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_top_right", mrb_cf_top_right, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_v2", mrb_cf_v2, MRB_ARGS_REQ(2));
  mrb_define_module_function(mrb, mCute, "cf_width", mrb_cf_width, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_x_axis", mrb_cf_x_axis, MRB_ARGS_REQ(1));
  mrb_define_module_function(mrb, mCute, "cf_y_axis", mrb_cf_y_axis, MRB_ARGS_REQ(1));
}
