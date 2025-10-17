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
		if (*(int *)engine->objects->data[i] == CYLINDER)
		{
			*type = CYLINDER;
			cylinder_hit(*((t_cylinder *)object), *ray, &hit);
		}
		if (*(int *)engine->objects->data[i] == PARABOLOID)
		{
			*type = PARABOLOID;
			paraboloid_hit(*((t_paraboloid *)object), *ray, &hit);
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

static void scale_by_factor(void *object, float dx, float dy)
{
	int type = *(int *)object;

	if (type == SPHERE)
	{
		(*(t_sphere *)object).r += 0.01f * -dx;
		if ((*(t_sphere *)object).r <= 0.05f)
			(*(t_sphere *)object).r = 0.05f;
	}
	if (type == CYLINDER)
	{
		(*(t_cylinder *)object).r += 0.01f * -dx;
		(*(t_cylinder *)object).h += 0.01f * dy;
		if ((*(t_cylinder *)object).r <= 0.05f)
			(*(t_cylinder *)object).r = 0.05f;
		if ((*(t_cylinder *)object).h <= 0.05f)
			(*(t_cylinder *)object).h = 0.05f;
	}
	if (type == LIGHT)
	{
		(*(t_light *)object).r += 0.01f * -dx;
		if ((*(t_light *)object).r <= 0.05f)
			(*(t_light *)object).r = 0.05f;
	}
	if (type == PARABOLOID)
	{
		(*(t_paraboloid *)object).focal += 0.01f * -dx;
		(*(t_paraboloid *)object).h += 0.01f * dy;
		if ((*(t_paraboloid *)object).focal <= 0.05f)
			(*(t_paraboloid *)object).focal = 0.05f;
		if ((*(t_paraboloid *)object).h <= 0.05f)
			(*(t_paraboloid *)object).h = 0.05f;
	}
}

void    scale_object(void *obj, double x, double y)
{
	t_mouse mouse = get_engine()->mouse;
	(void)x;
	(void)y;
	float 			dx = mouse.prev_pos.x - mouse.pos.x;
	float 			dy = mouse.prev_pos.y - mouse.pos.y;
	scale_by_factor(obj, dx, dy);
}
