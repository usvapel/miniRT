#include "minirt.h"

static t_vec3d hit_normal(t_ray ray, int axis);

bool    aabb_intersection(t_cube cube, t_ray ray, float *tnear, int *axis)
{
    float tmin = -FLT_MAX;
    float tmax =  FLT_MAX;
    float t1;
    float t2;
    int i;

    i = -1;
    tmin = -FLT_MAX;
    tmax =  FLT_MAX;
    while (++i < 3)
    {
        if (((float *)&ray.udir)[i] == 0.0f)
            continue;
        t1 = compute_axis_tbounds(cube, ray, i, false);
        t2 = compute_axis_tbounds(cube, ray, i, true);
        set_min_max_tbounds(&t1, &t2, &tmin, &tmax);
        if (t1 == tmin)
            *axis = i;
        if (tmin > tmax)
            return false; 
    }
    *tnear = tmin;
    return true;
}

bool cube_hit(t_cube *cube, t_ray ray, t_hit *hit)
{
    const t_basis3d local = build_local_basis(cube->axis);
    const t_ray lray = local_ray(ray, local, cube->base.pos);
    float tnear;
    t_vec3d pos;
    
    if (!aabb_intersection(new_cube(cube->h, cube->w), lray, &tnear, &hit->face_axis) || tnear < 0.0f)
        return false;
    pos = get_point_on_ray(lray, tnear);
    pos = point_from_basis(pos, local, cube->base.pos);
    if (!set_hit(cube, pos, ray, hit))
        return false;
    hit->normal = hit_normal(lray, hit->face_axis);
    hit->normal = point_from_basis(hit->normal, local, new_vec3d(0,0,0));
    return true;
}

static t_vec3d hit_normal(t_ray ray, int axis)
{
    t_vec3d normal = new_vec3d(0, 0, 0);

    if (axis == 0)
    {
        if (ray.udir.x > 0)
            normal.x = -1.0f;
        else
            normal.x = 1.0f;
    }
    if (axis == 1)
    {
        if (ray.udir.y > 0)
            normal.y = -1.0f;
        else
            normal.y = 1.0f;
    }
    if (axis == 2)
    {
        if (ray.udir.z > 0)
            normal.z = -1.0f;
        else
            normal.z = 1.0f; 
    }
    return normal;
}

