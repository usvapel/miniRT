#include "minirt.h"

t_sphere *inside_object(t_ray *ray, double x, double y)
{
	t_engine *engine = get_engine();
	t_sphere *sphere;
	*ray = get_ray(x, y);
	t_hit hit;
	int i = 0;

	while (i < engine->object_count)
	{
		sphere = engine->objects[i];
		hit.prev_hit = false;
		sphere_hit(*sphere, *ray, &hit);
		if (hit.prev_hit)
			break ;
		i++;
	}
	if (hit.prev_hit)
		return (sphere);
	else
		return (NULL);
}

static void scale_by_factor(float d)
{
	t_engine *engine = get_engine();
	t_sphere *sphere = engine->objects[0];
	if (sphere->r >= 0.05f)
		sphere->r += 0.01f * d;
	if (sphere->r <= 0.05f)
		sphere->r = 0.05f;
}

void    scale_object(double x, double y)
{
	static double	previous_length;
	double			current_length;
	static t_vec3d	previous_mouse;
	t_vec3d			current_mouse;

	current_mouse = new_vec3d(x, y, 0);
	previous_length = pow_magnitude_vec3d(previous_mouse);
	current_length = pow_magnitude_vec3d(current_mouse);
	if (previous_length <= current_length)
		scale_by_factor(1);
	if (previous_length >= current_length)
		scale_by_factor(-1);
	previous_mouse = new_vec3d(x, y, 0);
	previous_length = current_length;
}
