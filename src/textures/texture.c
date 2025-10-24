#include "minirt.h"

void    apply_texture(t_hit *hit)
{
    t_object *base;

    if (!hit->obj)
        return;
    base = get_base_object(hit->obj);
    if (base->texture.index < 0)
        return;
    if (base->type == PLANE)
        plane_uv(*((t_plane *)hit->obj), hit);
    else if (base->type == SPHERE)
        sphere_uv(*((t_sphere *)hit->obj), hit);
}

t_color get_texel(mlx_texture_t *text, float u, float v)
{
	if (u < 0.0f) u = 0.0f;
	if (u > 1.0f) u = 1.0f;
	if (v < 0.0f) v = 0.0f;
	if (v > 1.0f) v = 1.0f;
	uint32_t x = floorf(u * text->width);
	uint32_t y = floorf(v * text->height);
	if (x >= text->width) x = text->width - 1;
	if (y >= text->height) y = text->height - 1;
	int w = text->width;
	int pixel_index = (y * w + x) * text->bytes_per_pixel;
	uint8_t *pixels = text->pixels;
	uint8_t r = pixels[pixel_index + 0];
	uint8_t g = pixels[pixel_index + 1];
	uint8_t b = pixels[pixel_index + 2];
	uint8_t a = pixels[pixel_index + 3];
	uint32_t color = (r << 24) | (g << 16) | (b << 8) | a;
	return int_to_color(color);
}
