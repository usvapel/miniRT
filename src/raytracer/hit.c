#include "minirt.h"

bool	set_hit(void *object, t_vec3d new_hit, t_ray ray, t_hit *hit)
{
	t_object *base;

	if (hit->prev_hit && closest_hit(ray.origin, hit->pos, new_hit))
	   return (false);
	if (object)
	{
		base = (t_object *)object;
		hit->type = base->type;
		hit->color = base->color;
	}
	hit->pos = new_hit;
	hit->prev_hit = true;
	hit->obj = object;
	return (true);
}

bool	closest_hit(t_vec3d pos, t_vec3d hit1, t_vec3d hit2)
{
	const float	pow_mag1 = pow_magnitude_vec3d(sub_vec3d(hit1, pos));
	const float	pow_mag2 = pow_magnitude_vec3d(sub_vec3d(hit2, pos));
	return (pow_mag1 < pow_mag2);
}

float	nearest_t(float t0, float t1)
{
	if (t0 > 0.0f && t1 > 0.0f)
		return (fminf(t0, t1));
	else if (t0 > 0.0f)
		return (t0);
	else
		return (t1);
}
