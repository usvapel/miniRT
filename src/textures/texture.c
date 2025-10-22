#include "minirt.h"

void    apply_texture(t_hit *hit)
{
    t_object *base;

    if (!hit->obj)
        return;
    base = get_base_object(hit->obj);
    if (base->texture.index < 0)
        return;
    if (base->type == PLANE)
        plane_uv(*((t_plane *)hit->obj), hit);
    else if (base->type == SPHERE)
        sphere_uv(*((t_sphere *)hit->obj), hit);
}