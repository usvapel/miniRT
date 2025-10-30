#include "minirt.h"

inline static float schlick_reflectance(float cosine, float ref_idx)
{
	float r0;
	float x;
	float x2;

	r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0 * r0;
	x = 1.0 - cosine;
	x2 = x * x;
	return (r0 + (1.0 - r0) * x2 * x2 * x);
}

static void calculate_face_normal(t_ray ray, t_hit *hit, float indice, bool *front_face, t_vec3d *normal, float *eta_ratio)
{
	*front_face = dot_vec3d(ray.udir, hit->normal) < 0.0f;
	if (*front_face)
	{
		*normal = hit->normal;
		*eta_ratio = (1.0f / indice);
	}
	else
	{
		*normal = nscale_vec3d(hit->normal, -1.0f);
		*eta_ratio = (indice / 1.0f);
	}
}

static t_vec3d refract(t_vec3d uv, t_vec3d n, float etai_over_etat, bool *total_ir)
{
	const float cos_theta = fminf(dot_vec3d(nscale_vec3d(uv, -1.0f), n), 1.0f);
	const float sin_theta = 1.0f - cos_theta * cos_theta;
	t_vec3d r_out_perp;
	float length_squared;
	t_vec3d r_out_parallel;

	if (etai_over_etat * etai_over_etat * sin_theta > 1.0f)
	{
		*total_ir =  true;
		return (new_vec3d(0,0,0));
	}
	if (schlick_reflectance(cos_theta, etai_over_etat) > 0.5f) // magic number
	{
		*total_ir = true;
		return (new_vec3d(0,0,0));
	}
	r_out_perp = nscale_vec3d(n, cos_theta);
	r_out_perp = add2_vec3d(uv, r_out_perp);
	r_out_perp = nscale_vec3d(r_out_perp, etai_over_etat);
	length_squared = dot_vec3d(r_out_perp, r_out_perp);
	r_out_parallel = nscale_vec3d(n, -sqrtf(fabs(1.0f - length_squared)));
	*total_ir = false;
	return (add2_vec3d(r_out_perp, r_out_parallel));
}

t_color handle_refraction(t_ray ray, t_hit *hit, float indice, float reflectance, int depth, int y)
{
	bool	front_face;
	t_vec3d	normal;
	float	eta_ratio;
	bool	should_reflect;
	t_vec3d	R;
	t_ray	reflected;
	t_color	reflect_color;

	calculate_face_normal(ray, hit, indice, &front_face, &normal, &eta_ratio);
	should_reflect = false;
	R = refract(ray.udir, normal, eta_ratio, &should_reflect);
	if (should_reflect)
	{
		R = reflect(ray.udir, normal);
		reflected = create_reflected_ray(hit->pos, normal, R, true);
	}
	else
		reflected = create_reflected_ray(hit->pos, normal, R, false);
	reflect_color = trace_ray(reflected, depth + 1, y);
	return (mix_colors(hit->color, reflect_color, reflectance));
}
