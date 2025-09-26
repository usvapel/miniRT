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
    t_vec3d tmp;
    float pow_mag1;
    float pow_mag2;

    tmp = hit1;
    minus_vec3d(&tmp, pos);
    pow_mag1 = pow_magnitude_vec3d(tmp);

    tmp = hit2;
    minus_vec3d(&tmp, pos);
    pow_mag2 = pow_magnitude_vec3d(tmp);
    return pow_mag1 < pow_mag2;    
}