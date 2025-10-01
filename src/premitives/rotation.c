#include "minirt.h"

void rotateX_vec3d(t_vec3d *vec, float angle)
{
    double rad = deg_to_radians(angle);
    float ny = vec->y * cos(rad) - vec->z * sin(rad);
    float nz = vec->y * sin(rad) + vec->z * cos(rad);
    vec->y = ny;
    vec->z = nz;
}

void rotateY_vec3d(t_vec3d *vec, float angle)
{
    double rad = deg_to_radians(angle);
    float nx = vec->x * cos(rad) + vec->z * sin(rad);
    float nz =  -vec->x * sin(rad) + vec->z * cos(rad);
    vec->x = nx;
    vec->z = nz;
}

void rotateZ_vec3d(t_vec3d *vec, float angle)
{
    double rad = deg_to_radians(angle);
    float nx = vec->x * cos(rad) - vec->y * sin(rad);
    float ny = vec->x * sin(rad) + vec->y * cos(rad);
    vec->x = nx;
    vec->y = ny;
}

void    rotateXYZ_vec3d(t_vec3d *vec, float angle)
{
    rotateX_vec3d(vec, angle);
    rotateY_vec3d(vec, angle);
    rotateZ_vec3d(vec, angle);
}