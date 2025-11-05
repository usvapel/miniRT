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
	int face_axis;
	int ignore_setting_face_axis;
	t_material material;
}	t_hit;

typedef struct s_refract
{
	bool front_face;
	t_vec3d normal;
	float eta_ratio;
	bool should_reflect;
	t_vec3d R;
	t_ray reflected;
	t_color reflect_color;
	float	reflectance;
	float	indice;
}	t_refract;

void	*raytracer(void *engine);
t_color trace_ray(t_ray ray, int depth, int y);
t_vec3d	get_point_on_ray(t_ray ray, float t);
t_ray	get_ray(int x, int y);
bool	set_hit(void *obj, t_vec3d new_hit, t_ray ray, t_hit *hit);
bool	closest_hit(t_vec3d pos, t_vec3d hit1, t_vec3d hit2);
float	nearest_t(float t0, float t1);
t_ray local_ray(t_ray ray, t_basis3d local, t_vec3d local_origin);

//refraction
t_color handle_refraction(t_refract *rf, t_ray ray, t_hit *hit, int depth, int y);

//reflection
t_color handle_reflection(t_ray ray, t_hit *hit, float reflectance, int depth, int y);
t_ray create_reflected_ray(t_vec3d hit_pos, t_vec3d normal, t_vec3d direction, bool offset_forward);

#endif // RAY_H
