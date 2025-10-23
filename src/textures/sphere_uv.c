#include "minirt.h"
void schecker_board(t_hit *hit, int texture_index, float u, float v);
void wrap_img_sphere(t_hit *hit, float u, float v);
void    sphere_uv(t_sphere sphere, t_hit *hit)
{
    t_vec3d lhit = sub_vec3d(hit->pos, sphere.base.pos);
    float theta = acosf(fmaxf(-1.0f, fminf(1.0f, lhit.y / sphere.r)));   
    float phi = atan2f(lhit.z, lhit.x);
    float u =  (phi + PI) / (2 * PI);
    float v = theta / PI;

    if (sphere.base.texture.type == CHECKERBOARD)
        schecker_board(hit, sphere.base.texture.index, u, v);
    if (sphere.base.texture.type == IMAGE)
        wrap_img_sphere(hit, u, v);
}

void schecker_board(t_hit *hit, int texture_index, float u, float v)
{
    t_vector *checkers = get_engine()->textures.checkers;
	t_checker *checkboard = (t_checker *)(checkers->data[texture_index]);
	int i_u = floorf((u * 10)/ checkboard->block_size);
	int i_v = floorf((v * 10) / checkboard->block_size);
	t_color color = ((i_u + i_v) % 2 == 0) ? checkboard->color1 : checkboard->color2;
    hit->color = color;
}
void wrap_img_sphere(t_hit *hit, float u, float v)
{
    t_object *base = get_base_object(hit->obj);
    t_image_text *text = get_engine()->textures.images->data[base->texture.index];
    hit->color = get_texel(text->texture, u, v);
}
