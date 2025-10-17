
#include "minirt.h"

bool light_hit(t_light light, t_ray ray, t_hit *hit)
{
	float t0;
	float t1;
	float disc;
	t_vec3d n_hit_pos;
	bool is_set = {0};

	disc = solve_sphere_hit(ray, new_sphere(light.pos, light.r), &t0, &t1);
	if (disc < 0.0f || (t0 < 0 && t1 < 0))
		return false;
	n_hit_pos = get_point_on_ray(ray, nearest_t(t0, t1));
    is_set = set_hit(n_hit_pos, light.color, hit);
	if (!is_set)
		return false;
	hit->color = light.color;
	hit->type = LIGHT;
    return true;
}
