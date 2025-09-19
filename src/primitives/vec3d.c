#include "primitives.h"

t_vec3d new_vec3d(float x, float y, float z)
{
    t_vec3d vec3d;

    vec3d.x = x;
    vec3d.y = y;
    vec3d.z = z;
    return vec3d;
}

void scale_vec3d(t_vec3d *vec, float scaler)
{
    vec->x *= scaler;
    vec->y *= scaler;
    vec->z *= scaler;
}

void    add_vec3d(t_vec3d *vec1, t_vec3d *vec2)
{
    vec1->x += vec2->x;
    vec1->y += vec2->y;
    vec1->z += vec2->z;
}

void    minus_vec3d(t_vec3d *vec1, t_vec3d *vec2)
{
    vec1->x -= vec2->x;
    vec1->y -= vec2->y;
    vec1->z -= vec2->z;
}