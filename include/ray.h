#ifndef RAY_H
# define RAY_H

# include "primitives.h"
# include <stdbool.h>

# define EPSILON 1e-4
# define BOUNCES 4

typedef struct s_material
{
	float reflect;
	float refract;
	bool should_refract;
	bool  ignore;
}	t_material;

typedef struct s_ray
{
	t_vec3d origin;
	t_vec3d udir;
}	t_ray;

typedef struct s_hit
{
	t_vec3d pos;
	t_color color;
	bool prev_hit;
	t_vec3d normal;
	int type;
	float distance;
	void *obj;
	t_material material;
}	t_hit;

void	*raytracer(void *engine);
t_vec3d	get_point_on_ray(t_ray ray, float t);
t_ray	get_ray(int x, int y);
bool	set_hit(void *obj, t_vec3d new_hit, t_ray ray, t_hit *hit);
bool	closest_hit(t_vec3d pos, t_vec3d hit1, t_vec3d hit2);
float	nearest_t(float t0, float t1);

#endif // RAY_H
