#include "minirt.h"

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