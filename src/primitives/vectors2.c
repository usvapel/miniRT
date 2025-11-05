#include "minirt.h"

void    minus_vec3d(t_vec3d *vec1, t_vec3d vec2)
{
    vec1->x -= vec2.x;
    vec1->y -= vec2.y;
    vec1->z -= vec2.z;
}

float    magnitude_vec3d(t_vec3d vec)
{
    return (sqrt(dot_vec3d(vec, vec)));
}

float    pow_magnitude_vec3d(t_vec3d vec)
{
    return (dot_vec3d(vec, vec));
}

t_vec3d normalize_vec3d(t_vec3d vec)
{
	t_vec3d norm;
	float scaler;

    scaler = (float) 1 / magnitude_vec3d(vec);
    norm = nscale_vec3d(vec, scaler);
	return norm;
}

void normlize_vec3d(t_vec3d *vec)
{
    const float magnitude = magnitude_vec3d(*vec);
    float scaler;

    if (isnan(magnitude) || magnitude <= 0.000001f) {
        vec->x = 0.0f;
        vec->y = 1.0f;
        vec->z = 0.0f;
        return;
    }
    scaler = 1.0f / magnitude;
    if (isnan(scaler) || isinf(scaler)) {
        vec->x = 0.0f;
        vec->y = 1.0f;
        vec->z = 0.0f;
        return;
    }
    scale_vec3d(vec, scaler);
}