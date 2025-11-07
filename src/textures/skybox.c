#include "minirt.h"

t_color skycolor(t_ray *ray, int y)
{
    const t_skybox *skybox = &get_engine()->skybox;
    float theta;
    float phi;
    float u;
    float v;
    
    if (!skybox)
        return (int_to_color(color_gradient(get_engine(), y)));
    theta = atan2(ray->udir.z, ray->udir.x);
    phi = acos(ray->udir.y);
    u = (theta + PI) / (2*PI);
    v = phi / PI;
    return get_texel(skybox->txt, u, v);
}
