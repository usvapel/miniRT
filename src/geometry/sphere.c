#include "minirt.h"

static float	sphere_discriminant(t_vec3d oc, t_vec3d dir, float r);

bool	sphere_hit(t_sphere *sphere, t_ray ray, t_hit *hit)
{
	t_basis3d	local;
	t_ray		lray;
	float		t[2];
	float		disc;
	t_vec3d		n_hit_pos;

	ft_memset(&t, 0, sizeof(float) * 2);
	local = build_local_basis(sphere->axis);
	lray = local_ray(ray, local, sphere->base.pos);
	t[0] = -1;
	t[1] = -1;
	disc = solve_sphere_hit(lray, new_sphere(new_vec3d(0, 0, 0), sphere->r),
			&t[0], &t[1]);
	if (disc < 0.0f || (t[0] < 0.0f && t[1] < 0.0f))
		return (false);
	n_hit_pos = get_point_on_ray(lray, nearest_t(t[0], t[1]));
	n_hit_pos = point_from_basis(n_hit_pos, local, sphere->base.pos);
	if (!set_hit(sphere, n_hit_pos, ray, hit))
		return (false);
	hit->normal = sub_vec3d(hit->pos, sphere->base.pos);
	hit->type = SPHERE;
	hit->color = sphere->base.color;
	hit->material = sphere->base.material;
	return (true);
}

float	solve_sphere_hit(t_ray ray, t_sphere sphere, float *t0, float *t1)
{
	const t_vec3d	oc = sub_vec3d(ray.origin, sphere.base.pos);
	const float		a = dot_vec3d(ray.udir, ray.udir);
	const float		b = 2.0f * dot_vec3d(ray.udir, oc);
	const float		disc = sphere_discriminant(oc, ray.udir, sphere.r);
	const float		s = sqrt(disc);

	if (disc >= 0.0f)
	{
		*t0 = (-b - s) / (2.0f * a);
		*t1 = (-b + s) / (2.0f * a);
	}
	return (disc);
}

t_sphere	new_sphere(t_vec3d pos, float r)
{
	t_sphere	sphere;

	sphere.base.pos = pos;
	sphere.r = r;
	sphere.base.type = SPHERE;
	return (sphere);
}

static float	sphere_discriminant(t_vec3d oc, t_vec3d dir, float r)
{
	float	a;
	float	b;
	float	c;

	a = dot_vec3d(dir, dir);
	b = 2.0f * dot_vec3d(dir, oc);
	c = dot_vec3d(oc, oc) - (r * r);
	return ((b * b) - (4.0f * a * c));
}
