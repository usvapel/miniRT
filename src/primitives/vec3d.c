#include "minirt.h"

t_vec3d multiply_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d new = {0};
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
    float magnitude = magnitude_vec3d(*vec);
    if (isnan(magnitude) || magnitude <= 0.000001f) {
        vec->x = 0.0f;
        vec->y = 1.0f;
        vec->z = 0.0f;
        return;
    }
    float scaler = 1.0f / magnitude;
    if (isnan(scaler) || isinf(scaler)) {
        vec->x = 0.0f;
        vec->y = 1.0f;
        vec->z = 0.0f;
        return;
    }
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

t_vec3d project_vec3d(t_vec3d vec, t_vec3d to)
{
    t_vec3d tmp;
    float scale;

    tmp = to;
    scale = dot_vec3d(vec, to) / dot_vec3d(to, to);
    scale_vec3d(&tmp, scale);
   return tmp; 
}

t_vec3d sub_vec3d(t_vec3d vec, t_vec3d vec2)
{
    t_vec3d res;

    res = vec;
    minus_vec3d(&res, vec2);
    return res;
}

t_vec3d add2_vec3d(t_vec3d vec, t_vec3d vec2)
{
    t_vec3d res;

    res = vec;
    add_vec3d(&res, vec2);
    return res;
}
