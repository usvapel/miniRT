#include "minirt.h"

// Rodrigues' rotation formula
void rotate_vec3d(t_vec3d *v, t_vec3d axis, float angle)
{
	normlize_vec3d(&axis);
	float cos_theta = cosf(angle);
	float sin_theta = sinf(angle);
	t_vec3d part1 = nscale_vec3d(*v, cos_theta); // v * cos(theta)
	t_vec3d part2 = nscale_vec3d(cross_vec3d(axis, *v), sin_theta); // (k x v) * sin(theta)
	t_vec3d part3 = nscale_vec3d(axis, dot_vec3d(axis, *v) * (1 - cos_theta)); // k * (k . v) * (1 - cos(theta))
	*v = add2_vec3d(add2_vec3d(part1, part2), part3);
}

void rotateX_vec3d(t_vec3d *vec, float angle)
{
    const double rad = deg_to_radians(angle);
    const float ny = vec->y * cos(rad) - vec->z * sin(rad);
    const float nz = vec->y * sin(rad) + vec->z * cos(rad);
    
    vec->y = ny;
    vec->z = nz;
}

void rotateY_vec3d(t_vec3d *vec, float angle)
{
    double rad = deg_to_radians(angle);
    const float nx = vec->x * cos(rad) + vec->z * sin(rad);
    const float nz =  -vec->x * sin(rad) + vec->z * cos(rad);

    vec->x = nx;
    vec->z = nz;
}

void rotateZ_vec3d(t_vec3d *vec, float angle)
{
    const double rad = deg_to_radians(angle);
    const float nx = vec->x * cos(rad) - vec->y * sin(rad);
    const float ny = vec->x * sin(rad) + vec->y * cos(rad);

    vec->x = nx;
    vec->y = ny;
}

void    rotateXYZ_vec3d(t_vec3d *vec, float angle)
{
    rotateX_vec3d(vec, angle);
    rotateY_vec3d(vec, angle);
    rotateZ_vec3d(vec, angle);
}
