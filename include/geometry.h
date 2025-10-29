#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "primitives.h"
# include "stdbool.h"
# include "ray.h"
# include "textures.h"

# define LIGHT_RADIUS 0.3f

typedef struct s_object
{
	int			type;
	t_vec3d		pos;
	t_color		color;
	t_material	material;
	t_texture	texture;
} t_object;

typedef struct s_sphere
{
	t_object base;	
	float r;
}	t_sphere;

typedef struct s_plane
{
	t_object base;
	t_vec3d normal;
}	t_plane;

typedef struct s_cylinder
{
	t_object base;
	float h;
	float r;
	t_vec3d axis;
}	t_cylinder;

typedef struct s_circle
{
	t_object base;
	float r;
} t_circle;

typedef struct s_paraboloid
{
	t_object base;
	float	focal;
	float	h;
	t_vec3d axis;
} t_paraboloid;

typedef struct s_light
{
	t_object base;
	float r;
	float	brightness;
}	t_light;

typedef struct s_ambient
{
	t_object base;
	float	ratio;
}	t_ambient;

typedef enum e_id
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER, 
	PARABOLOID
} t_id ;

t_sphere	new_sphere(t_vec3d pos, float r);
bool		sphere_hit(t_sphere *sphere, t_ray ray, t_hit *hit);
float		solve_sphere_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
bool		plane_hit(t_plane *plane, t_ray ray, t_hit *hit);
bool		solve_plane_hit(t_plane plane, t_ray ray, float *t);
void		cylinder_hit(t_cylinder *cy, t_ray ray, t_hit *hit);
t_circle	new_circle(t_vec3d pos, float r);
bool		circle_hit(t_circle circ, t_ray ray, float *t0, float *t1);
bool paraboloid_hit(t_paraboloid *para, t_ray ray, t_hit *hit);
bool	light_hit(t_light *light, t_ray ray, t_hit *hit);

#endif // GEOMETRY_H

