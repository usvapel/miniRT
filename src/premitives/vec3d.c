#include "minirt.h"

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

void    add_vec3d(t_vec3d *vec1, t_vec3d vec2)
{
    vec1->x += vec2.x;
    vec1->y += vec2.y;
    vec1->z += vec2.z;
}

void    minus_vec3d(t_vec3d *vec1, t_vec3d vec2)
{
    vec1->x -= vec2.x;
    vec1->y -= vec2.y;
    vec1->z -= vec2.z;
}

void    print_vec(t_vec3d vec, char *id)
{
    if (id)
		printf("%s ", id);
	printf("(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}

float    magnitude_vec3d(t_vec3d vec)
{
    return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}
float    pow_magnitude_vec3d(t_vec3d vec)
{
    return ((vec.x * vec.x) * (vec.x * vec.x) + (vec.y * vec.y) * (vec.y * vec.y) + (vec.z * vec.z) * (vec.z * vec.z));
}

void    normlize_vec3d(t_vec3d *vec)
{
    float scaler;

    scaler = (float) 1 / magnitude_vec3d(*vec);
    scale_vec3d(vec, scaler);
}

float dot_vec3d(t_vec3d vec, t_vec3d vec2)
{
    return ((vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z));
}

t_vec3d cross_vec3d(t_vec3d a, t_vec3d b)
{
    t_vec3d cross;

    cross.x = a.y * b.z - a.z * b.y;
    cross.y = -(a.x * b.z - a.z * b.x);
    cross.z = a.x * b.y - a.y * b.x;
    return cross;
}
