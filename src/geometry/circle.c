#include "minirt.h"

t_circle new_circle(t_vec3d pos, float r)
{
    t_circle circ;
    
    circ.pos = pos;
    circ.r = r;
    return circ;
}

bool circle_hit(t_circle circ, t_ray ray, float *t0, float *t1)
{
    t_vec3d oc = new_vec3d(ray.origin.x - circ.pos.x, ray.origin.y - circ.pos.y, ray.origin.z - circ.pos.z);
    float a = dot_vec3d(ray.udir, ray.udir);
    float b;
    float c;

    b = 2.0f * dot_vec3d(ray.udir, oc);
    c = dot_vec3d(oc, oc) - circ.r * circ.r;
    if (b * b - 4 * a * c < 0)
        return false;
    *t0 = (-b - sqrt(b*b - 4 * a * c) )/ (2.0f * a) ;
    *t1 = (-b + sqrt(b*b- 4 * a * c)) / (2.0f * a);
    return true;
}
