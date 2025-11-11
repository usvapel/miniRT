#include "minirt.h"

void	llchecker_board(t_hit *hit, int texture_index, float u, float v);
void	wrap_img_cube(t_hit *hit, int text_index, float u, float v);
void	map_uv_by_cube_face_axis(t_cube cube, t_hit *hit, float *u, float *v);

void	cube_uv(t_cube cube, t_hit *hit)
{
	float	u;
	float	v;

	map_uv_by_cube_face_axis(cube, hit, &u, &v);
	if (cube.base.texture.type == CHECKERBOARD)
		llchecker_board(hit, cube.base.texture.index, u, v);
	if (cube.base.texture.type == IMAGE)
		wrap_img_cube(hit, cube.base.texture.index, u, v);
}

void	llchecker_board(t_hit *hit, int texture_index, float u, float v)
{
	const t_vector	*checkers = get_engine()->textures.checkers;
	const t_checker	*checkboard = (t_checker *)(checkers->data[texture_index]);
	const int		i_u = floorf(u / checkboard->block_size);
	const int		i_v = floorf(v / checkboard->block_size);

	if ((i_u + i_v) % 2 == 0)
		hit->color = checkboard->color1;
	else
		hit->color = checkboard->color2;
}

void	wrap_img_cube(t_hit *hit, int txt_index, float u, float v)
{
	const t_image_text	*text = get_engine()->textures.images->data[txt_index];

	u /= text->block_size;
	v /= text->block_size;
	u -= floor(u);
	v -= floor(v);
	hit->color = get_texel(text->texture, u, v);
	if (text->bump)
		apply_normal_bump(text->bump, hit, u, v);
}

void	map_uv_by_cube_face_axis(t_cube cube, t_hit *hit, float *u, float *v)
{
 	t_basis3d tbn = build_tbn_basis(hit->normal);
    t_vec3d lhit = point_in_basis(hit->pos, tbn, cube.base.pos);
    float face_w;
	float face_h;

    if ( hit->face_axis  == 0)
	{
        face_w = cube.d;
        face_h = cube.h;
    } else if (hit->face_axis == 1)
	{
        face_w = cube.w;
        face_h = cube.d;
    } else {
        face_w = cube.w;
        face_h = cube.h;
    }
    *u = (lhit.x / face_w) + 0.5f;
    *v = (lhit.y / face_h) + 0.5f;
}
