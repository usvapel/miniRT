#include "minirt.h"

void    set_sphere_color(t_sphere sphere, t_hit *hit);

float max(float val1, float val2)
{
	if (val1 > val2)
		return val1;
	if (val2 > val1)
		return val2;
	return val1;
}

bool sphere_hit(t_sphere sphere, t_ray ray, t_hit *hit)
{
	float t0;
	float t1;
	float disc;
	t_vec3d n_hit_pos;
	bool is_set = {0};

	disc = solve_sphere_hit(ray, sphere, &t0, &t1);
	if (disc < 0.0f || (t0 < 0.0f && t1 < 0.0f))
		return false;
	n_hit_pos = get_point_on_ray(ray, nearest_t(t0, t1));
	is_set = set_hit(n_hit_pos, sphere.color, hit);
	if (is_set)
	{
		hit->normal = sub_vec3d(hit->pos, sphere.pos);
		hit->type = SPHERE;
		hit->color = sphere.color;
	}
    return true;
}

float solve_sphere_hit(t_ray ray, t_sphere sphere, float *t0, float *t1)
{
    const float a = dot_vec3d(ray.udir, ray.udir);
    t_vec3d ray_s_origin;
    t_vec3d tmp;
    float b;
    float c;
    float disc;
    float sqrt_disc;

    ray_s_origin = sphere.pos;
    minus_vec3d(&ray_s_origin, ray.origin);
    tmp = ray.udir;
    scale_vec3d(&tmp, -2);
    b = dot_vec3d(tmp, ray_s_origin);
    c = dot_vec3d(ray_s_origin, ray_s_origin) - (sphere.r * sphere.r);
    disc = (b * b) - (4.0f * a * c);
    if (disc >= 0.0f)
    {
        sqrt_disc = sqrt(disc);
        *t0 = (-b - sqrt_disc) / (2.0f * a);
        *t1 = (-b + sqrt_disc) / (2.0f * a);
    }
    return (disc);
}

t_sphere new_sphere(t_vec3d pos, float r)
{
    t_sphere sphere;

    sphere.pos = pos;
    sphere.r = r;
    sphere.type = SPHERE;
    return sphere;
}
