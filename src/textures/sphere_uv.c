#include "minirt.h"
void schecker_board(t_hit *hit, int texture_index, float u, float v);

void    sphere_uv(t_sphere sphere, t_hit *hit)
{
    t_vec3d n = normalize_vec3d(sub_vec3d(hit->pos, sphere.base.pos));
    float u = atan2(n.x, n.z) / (2*3.147) + 0.5;
    float v = n.y * 0.5 + 0.5;

    if (sphere.base.texture.type == CHECKERBOARD)
        schecker_board(hit, sphere.base.texture.index, u, v);
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
