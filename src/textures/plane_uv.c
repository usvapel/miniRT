#include "minirt.h"

void lchecker_board(t_hit *hit, int texture_index, float u, float v);
void wrap_img_plane(t_hit *hit, int text_index, t_vec3d uv);

void    plane_uv(t_plane plane, t_hit *hit)
{
    const t_basis3d local = build_local_basis(plane.normal);
    t_vec3d l_hit = {};

    l_hit = point_in_basis(hit->pos, local, new_vec3d(0,0,0));
    if (plane.base.texture.type == CHECKERBOARD)
        lchecker_board(hit, plane.base.texture.index, l_hit.x, l_hit.z);
    if (plane.base.texture.type == IMAGE)
        wrap_img_plane(hit, plane.base.texture.index, l_hit);
}

void lchecker_board(t_hit *hit, int texture_index, float u, float v)
{
    const t_vector *checkers = get_engine()->textures.checkers;
	const t_checker *checkboard = (t_checker *)(checkers->data[texture_index]);
	const int i_u = floorf(u / checkboard->block_size);
	const int i_v = floorf(v / checkboard->block_size);
	const t_color color = ((i_u + i_v) % 2 == 0) ? checkboard->color1 : checkboard->color2;
    
    hit->color = color;
}

void wrap_img_plane(t_hit *hit, int txt_index, t_vec3d uv)
{
    const t_image_text *text = get_engine()->textures.images->data[txt_index];

    uv.x /= 6.0;
    uv.z /= 6.0;
    uv.x -= floor(uv.x);
    uv.z -= floor(uv.z);
    hit->color = get_texel(text->texture, uv.x, uv.z);
    if (text->bump)
        apply_normal_bump(text->bump, hit, uv.x, uv.z);
}
