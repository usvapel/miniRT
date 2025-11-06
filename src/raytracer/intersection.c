#include "minirt.h"

bool	obj_intersection(void *obj, t_ray ray, t_hit *hit)
{
	t_object	*base;
	int			type;

	base = (t_object *)obj;
	type = base->type;
	if (type == PLANE)
		return (plane_hit(((t_plane *)obj), ray, hit));
	if (type == SPHERE)
		return (sphere_hit(((t_sphere *)obj), ray, hit));
	else if (type == CYLINDER)
		return (cylinder_hit(((t_cylinder *)obj), ray, hit));
	else if (type == LIGHT)
		return (light_hit(((t_generic_light *)obj), ray, hit));
	else if (type == PARABOLOID)
		return (paraboloid_hit(((t_paraboloid *)obj), ray, hit));
	else if (type == CUBE)
		return (cube_hit(((t_cube *)obj), ray, hit));
	else
		return (false);
}

int	objects_intersection(t_engine *engine, t_ray *ray, t_hit *hit)
{
	int	i;

	i = 0;
	while (i < engine->objects->count)
	{
		obj_intersection(engine->objects->data[i], *ray, hit);
		i++;
	}
	if (hit->prev_hit)
		normlize_vec3d(&hit->normal);
	return (hit->type);
}
