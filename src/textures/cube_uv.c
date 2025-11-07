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
	const t_basis3d	local = build_local_basis(cube.axis);
	const t_vec3d	l_hit = point_in_basis(hit->pos, local, cube.base.pos);

	if (hit->face_axis == 0)
	{
		*u = l_hit.z / cube.h;
		*v = l_hit.y / cube.h;
	}
	else if (hit->face_axis == 1)
	{
		*u = l_hit.x / cube.w;
		*v = l_hit.z / cube.h;
	}
	else if (hit->face_axis == 2)
	{
		*u = l_hit.x / cube.w;
		*v = l_hit.y / cube.h;
	}
}
