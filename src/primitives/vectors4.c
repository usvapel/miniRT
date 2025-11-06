#include "minirt.h"

inline float	dot_vec3d(t_vec3d vec, t_vec3d vec2)
{
	return ((vec.x * vec2.x) + (vec.y * vec2.y) + (vec.z * vec2.z));
}

inline t_vec3d	cross_vec3d(t_vec3d a, t_vec3d b)
{
	t_vec3d	cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = -(a.x * b.z - a.z * b.x);
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

inline t_vec3d	project_vec3d(t_vec3d vec, t_vec3d to)
{
	t_vec3d	tmp;
	float	scale;

	tmp = to;
	scale = dot_vec3d(vec, to) / dot_vec3d(to, to);
	scale_vec3d(&tmp, scale);
	return (tmp);
}

inline t_vec3d	sub_vec3d(t_vec3d vec, t_vec3d vec2)
{
	t_vec3d	res;

	res = vec;
	minus_vec3d(&res, vec2);
	return (res);
}

inline t_vec3d	add2_vec3d(t_vec3d vec, t_vec3d vec2)
{
	t_vec3d	res;

	res = vec;
	add_vec3d(&res, vec2);
	return (res);
}
