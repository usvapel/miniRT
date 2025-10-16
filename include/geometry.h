#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "primitives.h"
# include "stdbool.h"
# include "ray.h"

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

typedef struct s_cylinder
{
	int type;
	float h;
	float r;
	t_vec3d pos;
	t_vec3d axis;
	t_color color;
} t_cylinder;

typedef struct s_circle
{
	t_vec3d pos;
	float r;
} t_circle;


typedef enum e_id
{
	AMBIENT_LIGHNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
} t_id ;

t_sphere new_sphere(t_vec3d pos, float r);
bool sphere_hit(t_sphere sphere, t_ray ray, t_hit *hit);
float solve_sphere_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
bool plane_hit(t_plane plane, t_ray ray, t_hit *hit);
bool solve_plane_hit(t_plane plane, t_ray ray, float *t);
void cylinder_hit(t_cylinder cy, t_ray ray, t_hit *hit);


t_circle new_circle(t_vec3d pos, float r);
bool circle_hit(t_circle circ, t_ray ray, float *t0, float *t1);

#endif // GEOMETRY_H
