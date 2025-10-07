
#include "minirt.h"

float solve_for_light_hit(t_ray ray, t_light light, float *t0, float *t1)
{
    const float a = dot_vec3d(ray.udir, ray.udir);
    t_vec3d ray_s_origin;
    t_vec3d tmp;
    float b;
    float c;
    float disc;

    ray_s_origin = light.pos;
    minus_vec3d(&ray_s_origin, ray.origin);
    tmp = ray.udir;
    scale_vec3d(&tmp, -2);
    b = dot_vec3d(tmp, ray_s_origin);
    c = dot_vec3d(ray_s_origin, ray_s_origin) - (light.r * light.r);
	disc = (b * b) - (4.0f * a * c);
    if (disc >= 0.0f)
    {
        *t0 = (-b - sqrt(disc)) / (2.0f * a);
        *t1 = (-b + sqrt(disc)) / (2.0f * a);
    }
    return ((b * b) - (4 * a * c));
}

bool light_hit(t_light light, t_ray ray, t_hit *hit)
{
	float t0;
	float t1;
	float disc;
	t_vec3d hit1;
	t_vec3d hit2;
	bool is_set = {0};

	disc = solve_for_light_hit(ray, light, &t0, &t1);
	if (disc < 0.0f)
		return false;
	hit1 = get_point_on_ray(ray, t0);
	hit2 = get_point_on_ray(ray, t1);  
	if (disc == 0.0f || t0 < t1)
		is_set = set_hit(hit1, light.color, hit);
	else
		is_set = set_hit(hit2, light.color, hit);
	if (is_set)
		hit->color = light.color;
    return true;
}
