#include "minirt.h"

float solve_for_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
void    set_sphere_color(t_sphere sphere, t_hit *hit);

bool sphere_hit(t_sphere sphere, t_ray ray, t_hit *hit)
{
    float t0;
    float t1;
    float disc;
    t_vec3d hit1;
    t_vec3d hit2;
    bool is_set = {0};

    disc = solve_for_hit(ray, sphere, &t0, &t1);
    if (disc < 0 || (t0 < 0 && t1 < 0))
        return false;
    hit1 = get_point_on_ray(ray, t0);
    hit2 = get_point_on_ray(ray, t1);  
    if (disc == 0 || t0 < t1)
       is_set = set_hit(hit1, sphere.color, hit);
    else
        is_set = set_hit(hit2, sphere.color, hit);
    if (is_set)
        set_sphere_color(sphere, hit);
    return true;
}

float solve_for_hit(t_ray ray, t_sphere sphere, float *t0, float *t1)
{
    const float a = dot_vec3d(ray.udir, ray.udir);
    t_vec3d ray_s_origin;
    t_vec3d tmp;
    float b;
    float c;
    float disc;


    ray_s_origin = sphere.pos;
    minus_vec3d(&ray_s_origin, ray.origin);
    tmp = ray.udir;
    scale_vec3d(&tmp, -2);
    b = dot_vec3d(tmp, ray_s_origin);
    c = dot_vec3d(ray_s_origin, ray_s_origin) - (sphere.r * sphere.r);
    disc = (b * b) - (4.0f * a * c);
    if (disc >= 0.0f)
    {
        *t0 = (-b - sqrt(disc)) / (2.0f * a);
        *t1 = (-b + sqrt(disc)) / (2.0f * a);
    }
    return ((b * b) - (4 * a * c));
}
float max(float val1, float val2)
{
	if (val1 > val2)
		return val1;
	if (val2 > val1)
		return val2;
	return val2;
}
void    set_sphere_color(t_sphere sphere, t_hit *hit)
{
    t_light *light = get_engine()->objects->data[5];
    
    t_vec3d tmp = new_vec3d(hit->pos.x, hit->pos.y, hit->pos.z);
    minus_vec3d(&hit->pos, sphere.pos);
    t_vec3d light_dir = new_vec3d(light.pos.x, light.pos.y, light.pos.z);
    minus_vec3d(&light_dir, tmp);
    normlize_vec3d(&light_dir);
    normlize_vec3d(&hit->pos);
    float d = max(dot_vec3d(hit->pos, light_dir), 0.0f);
    apply_color(&hit->color, d);
}