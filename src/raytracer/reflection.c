#include "minirt.h"

t_ray create_reflected_ray(t_vec3d hit_pos, t_vec3d normal, t_vec3d direction, bool offset_forward)
{
	t_ray	reflected;
	float	epsilon_multiplier;

	if (offset_forward)
		epsilon_multiplier = EPSILON;
	else
		epsilon_multiplier = -EPSILON;
	reflected.origin = add2_vec3d(hit_pos, nscale_vec3d(normal, epsilon_multiplier));
	reflected.udir = normalize_vec3d(direction);
	return (reflected);
}

t_color handle_reflection(t_ray ray, t_hit *hit, float reflectance, int depth, int y)
{
	t_vec3d	R;
	t_ray	reflected;
	t_color	reflect_color;

	R = reflect(ray.udir, hit->normal);
	reflected = create_reflected_ray(hit->pos, hit->normal, R, true);
	reflect_color = trace_ray(reflected, depth + 1, y);
	return (mix_colors(hit->color, reflect_color, reflectance));
}
