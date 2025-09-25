#include "minirt.h"
#include "primitives.h"

float solve_for_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);

bool sphere_ray_hit(t_ray ray, t_sphere sphere)
{
    const float a = dot_vec3d(ray.udir, ray.udir);
    t_vec3d ray_s_origin;
    t_vec3d tmp;
    float b;
    float c;

    // print_vec(ray.origin, "Ray ori: ");
    // print_vec(ray.udir, "Ray dir: ");
    ray_s_origin = sphere.pos;
    minus_vec3d(&ray_s_origin, ray.origin);
    tmp = ray.udir;
    scale_vec3d(&tmp, -2);
    b = dot_vec3d(tmp, ray_s_origin);
    c = dot_vec3d(ray_s_origin, ray_s_origin) - (sphere.r * sphere.r);
    return ((b * b) - (4 * a * c) >= 0);
}

float sphere_ray_hit_test(t_ray ray, t_sphere sphere)
{
    const float a = dot_vec3d(ray.udir, ray.udir);
    t_vec3d ray_s_origin;
    t_vec3d tmp;
    float b;
    float c;

    // print_vec(ray.origin, "Ray ori: ");
    // print_vec(ray.udir, "Ray dir: ");
    ray_s_origin = sphere.pos;
    minus_vec3d(&ray_s_origin, ray.origin);
    tmp = ray.udir;
    scale_vec3d(&tmp, -2);
    b = dot_vec3d(tmp, ray_s_origin);
    c = dot_vec3d(ray_s_origin, ray_s_origin) - (sphere.r * sphere.r);
    return ((b * b) - (4 * a * c));
}


bool sphere_hit(t_sphere sphere, t_ray ray, t_vec3d *pos)
{
    float t0;
    float t1;
    float disc;
    t_vec3d hit;
    t_vec3d hit2;
    t_vec3d tmp;

    disc = solve_for_hit(ray, sphere, &t0, &t1);
    if (disc < 0)
        return false;
    hit = ray.origin;  
    tmp = ray.udir;
    scale_vec3d(&tmp, t0);
    add_vec3d(&hit, tmp);
    hit2 = ray.origin;  
    tmp = ray.udir;
    scale_vec3d(&tmp, t1);
    add_vec3d(&hit2, tmp);
	ft_memset(pos, 0, sizeof(t_vec3d));
    if (disc == 0 || t0 < t1)
        add_vec3d(pos, hit);
    else
		add_vec3d(pos, hit2);

	// normlize_vec3d(pos);
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
