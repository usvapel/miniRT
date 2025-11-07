#include "minirt.h"

void	schecker_board(t_hit *hit, int texture_index, float u, float v);
void	wrap_img_sphere(t_hit *hit, float u, float v);

void	sphere_uv(t_sphere sphere, t_hit *hit)
{
	t_basis3d	local;
	t_vec3d		lhit;
	float		theta;
	float		phi;
	float		uv[2];

	local = build_local_basis(sphere.axis);
	lhit = point_in_basis(hit->pos, local, sphere.base.pos);
	theta = acosf(fmaxf(-1.0f, fminf(1.0f, lhit.y / sphere.r)));
	phi = atan2f(-lhit.z, lhit.x);
	uv[0] = (phi + PI) / (2 * PI);
	uv[1] = theta / PI;
	if (sphere.base.texture.type == CHECKERBOARD)
		schecker_board(hit, sphere.base.texture.index, uv[0], uv[1]);
	if (sphere.base.texture.type == IMAGE)
		wrap_img_sphere(hit, uv[0], uv[1]);
}

void	schecker_board(t_hit *hit, int texture_index, float u, float v)
{
	const t_vector	*checkers = get_engine()->textures.checkers;
	const t_checker	*checkboard = (t_checker *)(checkers->data[texture_index]);
	const int		i_u = floorf((u * 10) / checkboard->block_size);
	const int		i_v = floorf((v * 10) / checkboard->block_size);

	if ((i_u + i_v) % 2 == 0)
		hit->color = checkboard->color1;
	else
		hit->color = checkboard->color2;
}

void	wrap_img_sphere(t_hit *hit, float u, float v)
{
	const t_object		*base = get_base_object(hit->obj);
	const t_vector		*txt_images = get_engine()->textures.images;
	const t_image_text	*text = txt_images->data[base->texture.index];

	hit->color = get_texel(text->texture, u, v);
	if (text->bump)
		apply_normal_bump(text->bump, hit, u, v);
}
