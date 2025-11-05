#include "geometry.h"
#include "minirt.h"
#include "math.h"
#include "primitives.h"

static bool    cylinder_disk_hit(t_cylinder cy, t_ray ray, t_hit *hit, int top);
static bool cylinder_body_hit(t_cylinder cy, t_ray ray, t_hit *hit);
static bool is_body_hit(t_cylinder cy, t_ray ray, t_hit *hit, float t);

bool    cylinder_hit(t_cylinder *cy, t_ray ray, t_hit *hit)
{
    t_hit local_hit;
    bool hit_is_set;

    hit_is_set = false;
    ft_memset(&local_hit, 0, sizeof(t_hit));
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
		hit->material = cy->base.material;
		return true;
    }
    return false;
}

static bool    cylinder_disk_hit(t_cylinder cy, t_ray ray, t_hit *hit, int top)
{
    t_plane p;
    t_vec3d lhit;
    float magni;
    t_vec3d tmp;
    float t;

    ft_memset(&lhit, 0, sizeof(t_vec3d));
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


static bool cylinder_body_hit(t_cylinder cy, t_ray ray, t_hit *hit)
{
    const t_basis3d cy_local = build_local_basis(cy.axis);
    const t_vec3d origin = sub_vec3d(cy.base.pos, nscale_vec3d(cy.axis, cy.h * 0.5));
    float t0;
    float t1;
    t_ray lray;

    lray = local_ray(ray, cy_local, origin);
    lray.udir.y = 0;
    lray.origin.y = 0;
    if (!circle_hit(new_circle(new_vec3d(0,0,0), cy.r), lray, &t0, &t1))
        return false;
    if (t0 < 0 && t1 < 0)
        return false;
    return (is_body_hit(cy, ray, hit, nearest_t(t0, t1)));
}

static bool is_body_hit(t_cylinder cy, t_ray ray, t_hit *hit, float t)
{
    const t_basis3d local = build_local_basis(cy.axis);
    const t_vec3d origin = sub_vec3d(cy.base.pos, nscale_vec3d(cy.axis, cy.h * 0.5));
    const t_ray lray = local_ray(ray, local, origin);
    t_vec3d pos;

    pos = get_point_on_ray(lray, t);
    if (pos.y < 0 || pos.y > cy.h)
        return false;
    pos = point_from_basis(pos, local, origin);
    if (!set_hit(NULL, pos, ray, hit))
        return false;
    pos = get_point_on_ray(lray, t); 
    minus_vec3d(&pos, new_vec3d(0, pos.y, 0));
    hit->normal = point_from_basis(pos, local, new_vec3d(0, 0, 0));
    return true;
}
