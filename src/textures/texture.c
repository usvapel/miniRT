#include "minirt.h"

void	apply_texture(t_hit *hit)
{
	t_object	*base;

	if (!hit->obj)
		return ;
	base = get_base_object(hit->obj);
	if (base->texture.index < 0)
		return ;
	if (get_engine()->textures.images->count <= base->texture.index)
		return ;
	if (base->type == PLANE)
		plane_uv(*((t_plane *)hit->obj), hit);
	else if (base->type == SPHERE)
		sphere_uv(*((t_sphere *)hit->obj), hit);
}

t_color	get_texel(mlx_texture_t *text, float u, float v)
{
	const uint8_t	*pixels = text->pixels;
	uint32_t		x;
	uint32_t		y;
	int				pixel_i;
	uint32_t		color;

	u = clamp(u, 0.0f, 1.0f);
	v = clamp(v, 0.0f, 1.0f);
	x = floorf(u * text->width);
	y = floorf(v * text->height);
	if (x >= text->width)
		x = text->width - 1;
	if (y >= text->height)
		y = text->height - 1;
	pixel_i = (y * text->width + x) * text->bytes_per_pixel;
	color = (pixels[pixel_i + 0] << 24) // r
		| (pixels[pixel_i + 1] << 16)   // g
		| (pixels[pixel_i + 2] << 8)    // b
		| pixels[pixel_i + 3];          // a
	return (int_to_color(color));
}
/*
	TBN space:
		T: u, (right, x-axis)
		B: v, (up, y-axis)
		N: n (forward, z-axis)
	Normal stored in the normal map defined in TBN space,
		to get the actual normal
	we just need to transform from TBN to world space
*/
void	apply_normal_bump(mlx_texture_t *txt_normal, t_hit *hit, float u,
		float v)
{
	const t_basis3d	TBN = build_TBN_basis(hit->normal);
	const t_color	col = get_texel(txt_normal, u, v);
	t_vec3d			lnormal;

	lnormal = new_vec3d(col.r / 255, col.g / 255, col.b / 255);
	lnormal = sub_vec3d(nscale_vec3d(lnormal, 2), new_vec3d(1, 1, 1));
	hit->normal = point_from_basis(lnormal, TBN, hit->pos);
	normlize_vec3d(&hit->normal);
}
