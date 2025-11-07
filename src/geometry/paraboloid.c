#include "minirt.h"

float			solve_paraboloid_hit(t_ray ray, t_paraboloid para, float *t0,
					float *t1);
t_paraboloid	new_paraboloid(t_vec3d pos, t_vec3d axis, float focal);
bool			valid_params(float h, t_ray ray, float t0, float t1);
float			get_valid_param(float h, t_ray ray, float t0, float t1);
t_vec3d			surface_normal(t_vec3d hit, t_ray ray);

bool	paraboloid_hit(t_paraboloid *para, t_ray ray, t_hit *hit)
{
	const t_basis3d	p = build_local_basis(para->axis);
	const t_ray		r = local_ray(ray, p, para->base.pos);
	float			t[2];
	float			disc;
	t_vec3d			n_hit_pos;

	t[0] = -1;
	t[1] = -1;
	disc = solve_paraboloid_hit(r, new_paraboloid(new_vec3d(0, 0, 0),
				new_vec3d(0, 1, 0), para->focal), &t[0], &t[1]);
	if (disc < 0.0f || (t[0] < 0.0f && t[1] < 0.0f))
		return (false);
	if (!valid_params(para->h, r, t[0], t[1]))
		return (false);
	t[0] = get_valid_param(para->h, r, t[0], t[1]);
	n_hit_pos = get_point_on_ray(r, t[0]);
	n_hit_pos = point_from_basis(n_hit_pos, p, para->base.pos);
	if (!set_hit(para, n_hit_pos, ray, hit))
		return (false);
	n_hit_pos = get_point_on_ray(r, t[0]);
	hit->normal = surface_normal(n_hit_pos, r);
	hit->normal = point_from_basis(hit->normal, p, para->base.pos);
	return (true);
}

float	solve_paraboloid_hit(t_ray r, t_paraboloid para, float *t0, float *t1)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrt_disc;

	normlize_vec3d(&r.udir);
	a = (r.udir.z * r.udir.z + r.udir.x * r.udir.x);
	b = 2 * (r.origin.z * r.udir.z + r.origin.x * r.udir.x) - 4 * para.focal
		* r.udir.y;
	c = (r.origin.z * r.origin.z + r.origin.x * r.origin.x) - 4 * para.focal
		* r.origin.y;
	disc = (b * b) - (4.0f * a * c);
	if (disc >= 0.0f)
	{
		sqrt_disc = sqrt(disc);
		*t0 = (-b - sqrt_disc) / (2.0f * a);
		*t1 = (-b + sqrt_disc) / (2.0f * a);
	}
	return (disc);
}

bool	valid_params(float h, t_ray ray, float t0, float t1)
{
	t_vec3d	pos;
	t_vec3d	pos2;

	pos2 = get_point_on_ray(ray, t1);
	pos = get_point_on_ray(ray, t0);
	if (pos.y > h && pos2.y > h)
		return (false);
	if (t0 > 0.0f && t1 > 0.0f)
	{
		pos = get_point_on_ray(ray, fminf(t0, t1));
		pos2 = get_point_on_ray(ray, fmaxf(t0, t1));
		if (pos.y < h || pos2.y < h)
			return (true);
		return (false);
	}
	if (t0 > 0)
	{
		pos = get_point_on_ray(ray, t0);
		if (pos.y > h)
			return (false);
		return (true);
	}
	pos = get_point_on_ray(ray, t1);
	return (pos.y < h);
}

float	get_valid_param(float h, t_ray ray, float t0, float t1)
{
	t_vec3d	pos;
	t_vec3d	pos2;
	float	t;
	float	t2;

	pos = get_point_on_ray(ray, t0);
	pos2 = get_point_on_ray(ray, t1);
	if (t0 > 0.0f && t1 > 0.0f)
	{
		t = fminf(t0, t1);
		t2 = fmaxf(t0, t1);
		pos = get_point_on_ray(ray, t);
		pos2 = get_point_on_ray(ray, t2);
		if (pos.y < h)
			return (t);
		if (pos2.y < h)
			return (t2);
	}
	if (t0 > 0)
		return (t0);
	return (t1);
}

/*
	Given the surface implicit definition of paraboloid x^2 + z^2 - y = 0,
		the gradient ▽F=(2x, -1, 2z) vector at any
	gives us the normal of the surface n = ▽F / |▽F|
*/
t_vec3d	surface_normal(t_vec3d hit, t_ray ray)
{
	t_vec3d	n;

	n = new_vec3d(2 * hit.x, -1.0f, 2 * hit.z);
	if (dot_vec3d(nscale_vec3d(ray.udir, -1), n) < 0)
		scale_vec3d(&n, -1);
	normlize_vec3d(&n);
	return (n);
}
