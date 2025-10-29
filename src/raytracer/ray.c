#include "minirt.h"

t_ray	get_ray(int x, int y)
{
	const t_engine	*engine = get_engine();
	const t_vec3d	pixel = get_viewport_pixel(x, y);
	t_ray			ray;

	ray.origin = engine->camera.pos;
	ray.udir = pixel;
	minus_vec3d(&ray.udir, engine->camera.pos);
	normlize_vec3d(&ray.udir);
	return (ray);
}

t_vec3d	get_point_on_ray(t_ray ray, float t)
{
	t_vec3d	p;
	t_vec3d	tmp;

	p = ray.origin;
	tmp = ray.udir;
	scale_vec3d(&tmp, t);
	add_vec3d(&p, tmp);
	return (p);
}

t_ray local_ray(t_ray ray, t_basis3d local, t_vec3d local_origin)
{
    t_ray r;

    r.origin = point_in_basis(ray.origin, local, local_origin);
    r.udir = vec_in_basis(ray.udir, local);
    return r;
}