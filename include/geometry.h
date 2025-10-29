#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "primitives.h"
# include "stdbool.h"
# include "ray.h"
# include "textures.h"

typedef struct s_phong t_phong;

typedef struct s_object
{
	int type;
	bool is_light_source;
	bool semi_light_source;
	t_vec3d pos;
	t_vec3d *axis;
	t_color color;
	t_material material;
	t_texture texture;
} t_object;

typedef struct s_sphere
{
	t_object base;	
	float r;
	t_vec3d axis;
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

typedef struct s_generic_light
{
	t_object base;
	int obj_index;
	float brightness;
	void *light;
	void *obj;
} t_generic_light;

typedef struct s_point_light
{
	float r;
	t_vec3d axis;
} t_point_light;

typedef struct s_light
{
	float r;
	float	brightness;
}	t_light;

typedef struct s_ambient
{
	t_object base;
	float	ratio;
}	t_ambient;

typedef struct s_spot_light
{
	float brightness;
	float range;
	float fov;
	t_vec3d axis;
} t_spot_light;

typedef enum e_id
{
	AMBIENT,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER, 
	PARABOLOID,
	SPOT_LIGHT,
	POINT_LIGHT
} t_id ;

t_sphere	new_sphere(t_vec3d pos, float r);
bool		sphere_hit(t_sphere *sphere, t_ray ray, t_hit *hit);
float		solve_sphere_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
bool		plane_hit(t_plane *plane, t_ray ray, t_hit *hit);
bool		solve_plane_hit(t_plane plane, t_ray ray, float *t);
t_plane new_plane(t_vec3d pos, t_vec3d n);
bool		cylinder_hit(t_cylinder *cy, t_ray ray, t_hit *hit);
t_circle	new_circle(t_vec3d pos, float r);
bool		circle_hit(t_circle circ, t_ray ray, float *t0, float *t1);
bool paraboloid_hit(t_paraboloid *para, t_ray ray, t_hit *hit);
bool	light_hit(t_generic_light *light, t_ray ray, t_hit *hit);
bool spot_light_hit(t_generic_light *spot, t_hit *hit, t_phong *phong);
t_vec3d	adjusted_light_pos(t_generic_light light);
t_object *get_base_light(t_generic_light *light);

#endif // GEOMETRY_H

