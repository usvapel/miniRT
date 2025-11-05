#include "minirt.h"

bool	light_hit(t_generic_light *g_light, t_ray ray, t_hit *hit)
{
	if (!g_light->obj)
		return (false);
	return (obj_intersection(g_light->obj, ray, hit));
}

bool	spot_light_hit(t_generic_light *g_spot, t_hit *hit, t_phong *phong)
{
	t_ray	lray;
	float	t_h[2];
	float	r1;
	float	pos_hit;
	t_vec3d	pos;

	lray.origin = adjusted_light_pos(*g_spot);
	lray.udir = *get_base_light(g_spot)->axis;
	if (!solve_plane_hit(new_plane(hit->pos, phong->normal), lray, &t_h[0]))
		return (false);
	pos = get_point_on_ray(lray, t_h[0]);
	r1 = tanf(deg_to_radians(g_spot->spot_light.fov))
		* magnitude_vec3d(sub_vec3d(lray.origin, pos));
	t_h[1] = magnitude_vec3d(sub_vec3d(lray.origin, pos));
	pos_hit = magnitude_vec3d(sub_vec3d(pos, hit->pos));
	if (pos_hit > r1)
		return (false);
	scale_vec3d(&phong->light_color, smoothstep2(1 - pos_hit / r1, 0.5));
	scale_vec3d(&phong->light_color, smoothstep(1 - t_h[1]
			/ g_spot->spot_light.range));
	phong->light_color = color_to_vec3d(vec3d_to_color(phong->light_color));
	return (true);
}

t_vec3d	adjusted_light_pos(t_generic_light light)
{
	t_object	obj_base;
	t_ray		r;
	float		offset;

	if (!light.obj)
		return (light.base.pos);
	obj_base = *get_base_object(light.obj);
	r.origin = obj_base.pos;
	r.udir = *obj_base.axis;
	offset = 0.0f;
	if (obj_base.type == SPHERE)
		offset = ((t_sphere *)light.obj)->r;
	else if (obj_base.type == CYLINDER)
		offset = ((t_cylinder *)light.obj)->h / 2;
	else if (obj_base.type == PARABOLOID)
		offset = ((t_paraboloid *)light.obj)->h;
	return (get_point_on_ray(r, offset + 2 * 1e-2));
}

t_object	*get_base_light(t_generic_light *light)
{
	if (!light->obj)
		return (get_base_object(light));
	else
		return (get_base_object(light->obj));
}
