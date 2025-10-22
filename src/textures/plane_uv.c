#include "minirt.h"
void lchecker_board(t_hit *hit, int texture_index, float u, float v);

void    plane_uv(t_plane plane, t_hit *hit)
{
    const t_basis3d local = build_local_basis(plane.normal);
    t_uv_mapping map;
    t_vec3d l_hit = {};

    map.u = local.right;
    map.v = local.forward;
    l_hit = point_in_basis(hit->pos, local, plane.base.pos);
    if (plane.base.texture.type == CHECKERBOARD)
        lchecker_board(hit, plane.base.texture.index, l_hit.x, l_hit.z);
}
void    sphere_uv(t_sphere sphere, t_hit *hit)
{
    t_vec3d n = normalize_vec3d(sub_vec3d(hit->pos, sphere.base.pos));
    float u = atan2(n.x, n.z) / (2*3.147) + 0.5;
    float v = n.y * 0.5 + 0.5;

    if (sphere.base.texture.type == CHECKERBOARD)
        lchecker_board(hit, sphere.base.texture.index, u, v);
}

void lchecker_board(t_hit *hit, int texture_index, float u, float v)
{
    float checker_size = 0.09f;
    t_vector *checkers = get_engine()->textures.checkers;
	t_checker *checkboard = (t_checker *)(checkers->data[texture_index]);
	int i_u = floorf(u / checker_size);
	int i_v = floorf(v / checker_size);
	t_color color = ((i_u + i_v) % 2 == 0) ? checkboard->color1 : checkboard->color2;
    hit->color = color;
}
