
#include "minirt.h"

bool light_hit(t_generic_light *g_light, t_ray ray, t_hit *hit)
{
	if (!g_light->obj)
		return false;
	return obj_intersection(g_light->obj, ray, hit);
}

bool spot_light_hit(t_generic_light *g_spot, t_hit *hit, t_phong *phong)
{
	t_plane p = new_plane(hit->pos, phong->normal);
	t_object *base = get_base_light(g_spot);
	t_ray lray;
	float t;
	float r1;
	float pos_hit;
	t_vec3d pos;
	float h1;
	t_spot_light	*spot;
	float			h1;

	p = new_plane(hit->pos, phong->normal);
	base = get_base_light(g_spot);
	spot = &g_spot->spot_light;
	lray.origin = adjusted_light_pos(*g_spot);
	lray.udir = *base->axis;
	if (!solve_plane_hit(p, lray, &t))
		return false;
	pos = get_point_on_ray(lray, t);
	r1 = tanf(deg_to_radians(spot->fov))
		* magnitude_vec3d(sub_vec3d(lray.origin, pos));
	h1 = magnitude_vec3d(sub_vec3d(lray.origin, pos));
	pos_hit = magnitude_vec3d(sub_vec3d(pos, hit->pos));
	if (pos_hit > r1)
		return (false);
	scale_vec3d(&phong->light_color, smoothstep2(1 - pos_hit / r1, 0.5));
	scale_vec3d(&phong->light_color, smoothstep(1 - h1 / spot->range));
	phong->light_color = color_to_vec3d(vec3d_to_color(phong->light_color));
	return (true);
}

// t_vec3d	opague_by_distance(t_vec3d color, float d, float d_max)
// {
// 	t_color col = vec3d_to_color(color);

// 	col.a *= d_max / d;
// 	return (color_to_vec3d());
// }
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
