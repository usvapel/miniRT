#include "minirt.h"

t_vec3d multiply_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d new;

	new.x = one.x * two.x;
	new.y = one.y * two.y;
	new.z = one.z * two.z;
	return new;
}

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
t_vec3d nscale_vec3d(t_vec3d vec, float scaler)
{
    t_vec3d scaled;

    scaled = vec;
    scaled.x *= scaler;
    scaled.y *= scaler;
    scaled.z *= scaler;
    return scaled;
}
void    add_vec3d(t_vec3d *vec1, t_vec3d vec2)
{
    vec1->x += vec2.x;
    vec1->y += vec2.y;
    vec1->z += vec2.z;
}