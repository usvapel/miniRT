#include "minirt.h"

static float	get_distance(t_vec3d from, t_vec3d to)
{
	return (magnitude_vec3d(sub_vec3d(from, to)));
}

static bool	should_continue_shadow_trace(t_hit *shadow_hit, t_vec3d *shadow,
		float hit_distance, float light_distance)
{
	if (!shadow_hit->prev_hit
		|| get_base_object(shadow_hit->obj)->is_light_source)
		return (false);
	if (hit_distance > light_distance)
		return (false);
	if (shadow_hit->material.refract == -1)
	{
		*shadow = (t_vec3d){0, 0, 0};
		return (false);
	}
	if (shadow->x < EPSILON && shadow->y < EPSILON && shadow->z < EPSILON)
		return (false);
	return (true);
}

static t_vec3d	trace_shadow_path(t_vec3d *shadow, t_ray shadow_ray,
		t_vec3d light_pos)
{
	float	hit_distance;
	t_hit	shadow_hit;
	int		i;
	float	light_distance;

	i = -1;
	while (++i < BOUNCES)
	{
		shadow_hit = (t_hit){0};
		objects_intersection(get_engine(), &shadow_ray, &shadow_hit);
		hit_distance = get_distance(shadow_hit.pos, shadow_ray.origin);
		light_distance = get_distance(light_pos, shadow_ray.origin);
		if (!should_continue_shadow_trace(&shadow_hit, shadow, hit_distance,
				light_distance))
			return (*shadow);
		*shadow = nscale_vec3d(*shadow, fmaxf(0.5f, fminf(1.0f
						/ shadow_hit.material.refract, 1.0f)));
		if (shadow->x < EPSILON && shadow->y < EPSILON && shadow->z < EPSILON)
			return (*shadow);
		shadow_ray.origin = add2_vec3d(shadow_hit.pos,
				nscale_vec3d(shadow_ray.udir, EPSILON * 2));
	}
	return (*shadow);
}

t_vec3d	get_shadow_attenuation(t_phong *p, t_hit hit, t_generic_light light)
{
	t_vec3d	shadow;
	t_ray	shadow_ray;
	t_vec3d	light_pos;

	shadow = (t_vec3d){1.0, 1.0, 1.0};
	shadow_ray.origin = add2_vec3d(hit.pos, nscale_vec3d(p->nlight_dir,
				EPSILON));
	shadow_ray.udir = p->nlight_dir;
	light_pos = adjusted_light_pos(light);
	return (trace_shadow_path(&shadow, shadow_ray, light_pos));
}
