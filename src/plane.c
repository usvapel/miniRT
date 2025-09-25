#include "minirt.h"

/*
Point in ray: p = o + td, o is origin, d ray direction and t distance from origin
Plane in normal form: n * (r-r0) = 0, n normal form, r0 known point and r is any point in the plane, r == p
--> n * (o + td -r0) = 0
--> t = n*(r0 - o) / (d * n), if d * n == 0, ray is inside the plane,  n*(r0 - o) == 0 no solution
*/
bool plane_hit(t_plane plane, t_ray ray, t_hit *hit)
{
    const float d_dot_n = dot_vec3d(plane.normal, ray.udir);
    t_vec3d tmp;
    float t;

    if (d_dot_n == 0)
        return false;
    tmp = plane.pos; 
    minus_vec3d(&tmp, ray.origin);
    t = dot_vec3d(plane.normal, tmp);
    if (t == 0)
        return false;
    t /= d_dot_n;
    if (t < 0)
        return false;
    set_hit(get_point_on_ray(ray, t), plane.color, hit);
    return true;
}