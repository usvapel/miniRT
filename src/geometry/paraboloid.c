#include "minirt.h"
float solve_paraboloid_hit(t_ray ray, t_paraboloid para, float *t0, float *t1);

bool paraboloid_hit(t_paraboloid para, t_ray ray, t_hit *hit)
{
	float t0;
	float t1;
	float disc;
	t_vec3d n_hit_pos;

	disc = solve_paraboloid_hit(ray, para, &t0, &t1);
	if (disc < 0.0f || (t0 < 0.0f && t1 < 0.0f))
		return false;
	n_hit_pos = get_point_on_ray(ray, nearest_t(t0, t1));
	set_hit(n_hit_pos, para.color, hit);
    return true;
}

float solve_paraboloid_hit(t_ray ray, t_paraboloid para, float *t0, float *t1)
{
    t_vec3d o = ray.origin;
    minus_vec3d(&o, para.pos);
    const t_vec3d r = ray.udir;
    const float a = ray.udir.z * ray.udir.z + ray.udir.x * ray.udir.x;
    float b = 2 * (o.z * r.z + o.x * r.z) - r.y * para.focal;
    float c = o.z * o.z + o.x * o.x - o.y * para.focal;
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