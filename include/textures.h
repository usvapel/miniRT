#ifndef TEXTURES_H
# define TEXTURES_H

# include "MLX42.h"
# include "primitives.h"
# include "ray.h"
# include "vector.h"

typedef struct s_plane	t_plane;
typedef struct s_sphere	t_sphere;
typedef struct s_cube	t_cube;

typedef struct uv_mapping
{
	t_vec3d				u;
	t_vec3d				v;
}						t_uv_mapping;

typedef struct s_textures
{
	t_vector			*checkers;
	t_vector			*images;
}						t_textures;

typedef struct s_texture
{
	int					type;
	int					index;
}						t_texture;

typedef struct s_checker
{
	t_color				color1;
	t_color				color2;
	float				block_size;
}						t_checker;

typedef struct s_image_text
{
	mlx_texture_t		*texture;
	mlx_texture_t		*bump;
	char				*txt_source;
	char				*bump_source;
	float				block_size;
}						t_image_text;

typedef enum e_texture_type
{
	CHECKERBOARD,
	IMAGE
}						t_texture_type;

typedef struct s_skybox
{
	mlx_texture_t		*txt;
	char				*src;
}						t_skybox;

// apply texture
void					apply_texture(t_hit *hit);
t_color					get_texel(mlx_texture_t *text, float u, float v);
void					apply_normal_bump(mlx_texture_t *txt_normal, t_hit *hit,
							float u, float v);

// uv mappings
void					plane_uv(t_plane plane, t_hit *hit);
void					sphere_uv(t_sphere sphere, t_hit *hit);
void					cube_uv(t_cube cube, t_hit *hit);

t_color					skycolor(t_ray *ray, int y);
#endif
