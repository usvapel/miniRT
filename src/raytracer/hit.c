#include "minirt.h"

bool    set_hit(t_vec3d new_hit, t_color color, t_hit *hit)
{
    t_camera cam = get_engine()->camera;

   if (hit->prev_hit && closest_hit(cam.pos, hit->pos, new_hit))
       return false;
    hit->pos = new_hit;
    hit->color = color;
    hit->prev_hit = true;
    return true;
}

bool closest_hit(t_vec3d pos, t_vec3d hit1, t_vec3d hit2)
{
    float pow_mag1;
    float pow_mag2;

    pow_mag1 = pow_magnitude_vec3d(sub_vec3d(hit1, pos));

    pow_mag2 = pow_magnitude_vec3d(sub_vec3d(hit2, pos));
    return pow_mag1 < pow_mag2;    
}

float nearest_t(float t0, float t1)
{
    if (t0 > 0 && t1 > 0)
        return fminf(t0, t1);
    else if (t0 > 0)
        return t0;
    else
        return t1;
}
