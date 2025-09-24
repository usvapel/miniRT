#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "minirt.h"

typedef struct s_sphere
{
	int type;
	t_vec3d pos;
	float r;
	t_color color;
} t_sphere;


typedef struct s_plane
{
	int type;
	t_vec3d pos;
	t_vec3d normal;
	t_color color;
} t_plane;

typedef enum e_id
{
	AMBIENT_LIGHNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
} t_id ;

bool sphere_ray_hit(t_ray ray, t_sphere sphere);

#endif
