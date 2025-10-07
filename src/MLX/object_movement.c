#include "minirt.h"

void *inside_object(t_ray *ray, double x, double y, int *type)
{
	t_engine *engine = get_engine();
	void *object;
	*ray = get_ray(x, y);
	t_hit hit;
	int i = 0;

	while (i < engine->object_count)
	{
		object = engine->objects->data[i];
		hit.prev_hit = false;
		if (*(int *)engine->objects->data[i] == SPHERE)
		{
			*type = SPHERE;
			sphere_hit(*((t_sphere *)object), *ray, &hit);
		}
		if (*(int *)engine->objects->data[i] == LIGHT)
		{
			*type = LIGHT;
			light_hit(*((t_light *)object), *ray, &hit);
		}
		if (*(int *)engine->objects->data[i] == PLANE)
		{
			*type = PLANE;
			plane_hit(*((t_plane *)object), *ray, &hit);
		}
		if (hit.prev_hit)
			break ;
		i++;
	}
	if (hit.prev_hit)
		return (object);
	else
		return (NULL);
}

static void scale_by_factor(float d)
{
	static t_ray ray;
	int type;
	t_engine *engine = get_engine();

	void *object = inside_object(&ray, engine->mouse.pos.x, engine->mouse.pos.y, &type);
	if (!object)
		return ;
	if (type == SPHERE)
	{
		if ((*(t_sphere *)object).r >= 0.05f)
			(*(t_sphere *)object).r += 0.01f * d;
		if ((*(t_sphere *)object).r <= 0.05f)
			(*(t_sphere *)object).r = 0.05f;
	}
	if (type == LIGHT)
	{
		if ((*(t_light *)object).r >= 0.05f)
			(*(t_light *)object).r += 0.01f * d;
		if ((*(t_light *)object).r <= 0.05f)
			(*(t_light *)object).r = 0.05f;
	}
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
