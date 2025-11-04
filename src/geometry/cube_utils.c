#include "minirt.h"

float compute_axis_tbounds(t_cube cube, t_ray ray, int index, bool max)
{
    const float origin = ((float *)&ray.origin)[index];
    const float dir    = ((float *)&ray.udir)[index];
    const float minB   = ((float *)&cube.min)[index];
    const float maxB   = ((float *)&cube.max)[index];

    if (max)
        return (maxB - origin) / dir;
    return (minB - origin) / dir;
}
void swap_vals(float *val1, float *val2)
{
    float tmp;

    tmp = *val1;
    *val1 = *val2;
    *val2 = tmp;
}

void set_min_max_tbounds(float *t1, float *t2, float *tmin, float *tmax)
{
    if (*t1 > *t2)
        swap_vals(t1, t2);
    if (*t1 > *tmin)
        *tmin = *t1;
    if (*t2 < *tmax)
        *tmax = *t2; 
}


static t_cube new_cube(float h, float w)
{
    t_cube cube = {0};
    set_cube_min_max(&cube, h, w);
    return cube;
}
