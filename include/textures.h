#ifndef TEXTURES_H
#define TEXTURES_H

#include "vector.h"

typedef struct s_plane t_plane;
typedef struct s_sphere t_sphere;

typedef struct uv_mapping
{
    t_vec3d u;
    t_vec3d v;
} t_uv_mapping;

typedef struct s_textures
{
    t_vector *checkers;
    t_vector *images;
} t_textures;

typedef struct s_texture
{
    int type;
    int index;
} t_texture;

typedef struct s_checker
{
    t_color color1;
    t_color color2;
    float block_size;
} t_checker;

typedef enum e_texture_type
{
	CHECKERBOARD,
	IMAGE
} t_texture_type ;


// apply texture
void    apply_texture(t_hit *hit);

// uv mappings
void    plane_uv(t_plane plane, t_hit *hit);
void    sphere_uv(t_sphere sphere, t_hit *hit);

#endif