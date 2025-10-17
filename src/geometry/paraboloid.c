#include "minirt.h"
float solve_paraboloid_hit(t_ray ray, t_paraboloid para, float *t0, float *t1);
t_paraboloid new_paraboloid(t_vec3d pos, t_vec3d axis, float focal);
bool valid_params(float h, t_ray ray, float t0, float t1);
float get_valid_param(float h, t_ray ray, float t0, float t1);
t_vec3d surface_normal(t_vec3d hit, t_ray ray);

bool paraboloid_hit(t_paraboloid para, t_ray ray, t_hit *hit)
{
	float t0;
	float t1;
	float disc;
	t_vec3d n_hit_pos;
    t_basis3d p = build_local_basis(para.axis); // builds new coords along para axis, para.pos is the origin in world space
    t_ray r; // ray in new coords
    float t;

    r.origin = point_in_basis(ray.origin, p, para.pos);
    r.udir = vec_in_basis(ray.udir, p);
	disc = solve_paraboloid_hit(r, new_paraboloid(new_vec3d(0, 0, 0), new_vec3d(0, 1, 0), para.focal), &t0, &t1);
	if (disc < 0.0f || (t0 < 0.0f && t1 < 0.0f))
		return false;
    if (!valid_params(para.h, r, t0, t1))
        return false;
    t = get_valid_param(para.h, r, t0, t1);
    n_hit_pos = get_point_on_ray(r, t); // hit in object coords
    n_hit_pos = point_from_basis(n_hit_pos, p, para.pos); // convert from object to world point
    if (!set_hit(n_hit_pos, para.color, hit))
        return false;
    n_hit_pos = get_point_on_ray(r, t);
    hit->normal = surface_normal(n_hit_pos, r);
    hit->normal = point_from_basis(hit->normal, p, para.pos);
    hit->type = PARABOLOID;
    return true;
}

float solve_paraboloid_hit(t_ray ray, t_paraboloid para, float *t0, float *t1)
{
    t_vec3d o = ray.origin;
    t_vec3d r = ray.udir;
    normlize_vec3d(&r);
    (void) para;
    const float a = (r.z * r.z + r.x * r.x);
    float b = 2 * (o.z * r.z + o.x * r.x) - 4 * para.focal * r.y;
    float c = (o.z * o.z + o.x * o.x) - 4 * para.focal * o.y;
    float disc = (b * b) - (4.0f * a * c);
    float sqrt_disc;
    if (disc >= 0.0f)
    {
        sqrt_disc = sqrt(disc);
        *t0 = (-b - sqrt_disc) / (2.0f * a);
        *t1 = (-b + sqrt_disc) / (2.0f * a);
    }
    return (disc);
}

t_paraboloid new_paraboloid(t_vec3d pos, t_vec3d axis, float focal)
{
    t_paraboloid para;
    para.pos = pos;
    para.axis = axis;
    para.focal = focal;
    return para;
}

bool valid_params(float h, t_ray ray, float t0, float t1)
{
    t_vec3d pos = get_point_on_ray(ray, t0);
    t_vec3d pos2 = get_point_on_ray(ray, t1);

    if (pos.y > h && pos2.y > h)
        return false;
    if (t0 > 0.0f && t1 > 0.0f)
    {
        pos = get_point_on_ray(ray, fminf(t0, t1)); // near hit
        pos2 = get_point_on_ray(ray, fmaxf(t0, t1)); // far hit
        if (pos.y < h)
            return true;
        if (pos2.y < h)
            return true;
        return false;
    }
    if (t0 > 0)
    {
        pos = get_point_on_ray(ray, t0);
        if (pos.y > h)
            return false;
        return true;
    }
    pos = get_point_on_ray(ray, t1);
    if (pos.y > h)
        return false;
    return true;
}

float get_valid_param(float h, t_ray ray, float t0, float t1)
{
    t_vec3d pos = get_point_on_ray(ray, t0);
    t_vec3d pos2 = get_point_on_ray(ray, t1);
    float t;
    float t2;

    if (t0 > 0.0f && t1 > 0.0f)
    {
        t = fminf(t0, t1);
        t2 = fmaxf(t0, t1);
        pos = get_point_on_ray(ray, t);
        pos2 = get_point_on_ray(ray, t2);
        if (pos.y < h)
            return t;
        if (pos2.y < h)
            return t2;
    }
    if (t0 > 0)
        return t0;
    return t1;
}

/*
    Given the surface implicit definition of paraboloid x^2 + z^2 - y = 0, the gradient ▽F=(2x, -1, 2z) vector at any
    gives us the normal of the surface n = ▽F / |▽F|
*/
t_vec3d surface_normal(t_vec3d hit, t_ray ray)
{
    t_vec3d n;
    (void)ray;
    n = new_vec3d(2 * hit.x, -1.0f, 2 * hit.z);
    if (dot_vec3d(nscale_vec3d(ray.udir, -1), n) < 0)
        scale_vec3d(&n, -1);
    normlize_vec3d(&n);
    return n;
}