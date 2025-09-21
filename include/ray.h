#ifndef RAY_H
#define RAY_H

#include "primitives.h"

typedef struct s_ray
{
    t_vec3d origin;
    t_vec3d udir;
} t_ray;

void    raytracer(void *engine);

#endif