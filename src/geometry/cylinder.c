#include "geometry.h"
#include "minirt.h"
#include "math.h"
bool    cylinder_disk_hit(t_cylinder cy, t_ray ray, t_hit *hit, int top);
bool circle_hit(t_circle circ, t_ray ray, float *t0, float *t1);
bool cylinder_body_hit(t_cylinder cy, t_ray ray, t_hit *hit);

bool    cylinder_hit(t_cylinder *cy, t_ray ray, t_hit *hit)
{
    t_hit local_hit = {0};
    bool hit_is_set;

    hit_is_set = false;
    if (cylinder_disk_hit(*cy, ray, &local_hit, 1))
        hit_is_set = set_hit(cy, local_hit.pos, ray, hit);
    if (cylinder_disk_hit(*cy, ray, &local_hit, -1))
        hit_is_set = set_hit(cy, local_hit.pos, ray, hit);
    if (cylinder_body_hit(*cy, ray, &local_hit))
        hit_is_set = set_hit(cy, local_hit.pos, ray, hit);
    if (hit_is_set)
    {
        hit->color = cy->base.color;
        hit->normal = local_hit.normal;
        hit->pos = local_hit.pos;
        hit->type = CYLINDER;
        return true;
    }
    return false;
}

bool    cylinder_disk_hit(t_cylinder cy, t_ray ray, t_hit *hit, int top)
{
    t_plane p;
    t_vec3d lhit = {0};
    float magni;
    t_vec3d tmp;
    float t;

    p.base.color = cy.base.color;
    p.base.pos = cy.base.pos;
    p.normal = cy.axis;
    add_vec3d(&p.base.pos, nscale_vec3d(cy.axis, top * cy.h * 0.5));
    if (!solve_plane_hit(p, ray, &t))
        return false;
    if (t < 0)
        return false;
    lhit = get_point_on_ray(ray, t);
    tmp = lhit;
    minus_vec3d(&tmp, p.base.pos);
    magni = magnitude_vec3d(tmp);
    if (magni > cy.r)
        return false;
    if (!set_hit(NULL, lhit, ray, hit))
        return false;
    hit->normal = nscale_vec3d(cy.axis, top);
    return true; 
}


bool cylinder_body_hit(t_cylinder cy, t_ray ray, t_hit *hit)
{
    t_basis3d cy_local = build_local_basis(cy.axis);
    t_ray ray_cy_base;
    t_vec3d origin = sub_vec3d(cy.base.pos, nscale_vec3d(cy.axis, cy.h * 0.5));
    float t0;
    float t1;
    t_vec3d pos;
    t_ray tmp;

    ray_cy_base.udir = vec_in_basis(ray.udir, cy_local);
    ray_cy_base.origin = point_in_basis(ray.origin, cy_local, origin);
    tmp = ray_cy_base;
    tmp.udir.y = 0;
    tmp.origin.y = 0;
    if (!circle_hit(new_circle(new_vec3d(0,0,0), cy.r), tmp, &t0, &t1))
        return false;
    if (t0 < 0 && t1 < 0)
        return false;
    pos = get_point_on_ray(ray_cy_base, nearest_t(t0, t1));
    if (pos.y < 0 || pos.y > cy.h)
        return false;
    pos = point_from_basis(pos, cy_local, origin);
    if (!set_hit(NULL, pos, ray, hit))
        return false;
    pos = get_point_on_ray(ray_cy_base, nearest_t(t0, t1)); 
    minus_vec3d(&pos, new_vec3d(0, pos.y, 0));
    hit->normal = point_from_basis(pos, cy_local, new_vec3d(0, 0, 0));
    return true; 
}

// bool cylinder_body_hit(t_cylinder cy, t_ray ray, t_hit *hit)
// {
//     t_vec3d base_pos = new_vec3d(cy.pos.x, 0, cy.pos.z);
//     t_ray proj_ray_to_y;
//     float t0;
//     float t1;
//     t_vec3d pos;
//     float magni;

//     proj_ray_to_y.origin = new_vec3d(ray.origin.x, 0, ray.origin.z);
//     proj_ray_to_y.udir = project_vec3d(ray.udir, new_vec3d(0, 1, 0));
//     if (!circle_hit(new_circle(base_pos, cy.r), proj_ray_to_y, &t0, &t1))
//         return false;
//     if (t0 < t1)
//         pos = get_point_on_ray(proj_ray_to_y, t0);
//     else
//         pos = get_point_on_ray(proj_ray_to_y, t1);
//     minus_vec3d(&pos, base_pos);
//     magni = magnitude_vec3d(pos);
//     if (magni < 0 || magni > cy.h)
//         return false;
//     add_vec3d(&pos, base_pos);
//     hit->pos = pos;
//     return true;
// }
