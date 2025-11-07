#include "minirt.h"

// Rodrigues' rotation formula
void	rotate_vec3d(t_vec3d *v, t_vec3d axis, float angle)
{
	float	cos_theta;
	float	sin_theta;
	t_vec3d	part1;
	t_vec3d	part2;
	t_vec3d	part3;

	normlize_vec3d(&axis);
	cos_theta = cosf(angle);
	sin_theta = sinf(angle);
	part1 = nscale_vec3d(*v, cos_theta);
	part2 = nscale_vec3d(cross_vec3d(axis, *v), sin_theta);
	part3 = nscale_vec3d(axis, dot_vec3d(axis, *v) * (1 - cos_theta));
	*v = add2_vec3d(add2_vec3d(part1, part2), part3);
}

void	rotatex_vec3d(t_vec3d *vec, float angle)
{
	const float	rad = deg_to_radians(angle);
	const float	ny = vec->y * cos(rad) - vec->z * sin(rad);
	const float	nz = vec->y * sin(rad) + vec->z * cos(rad);

	vec->y = ny;
	vec->z = nz;
}

void	rotatey_vec3d(t_vec3d *vec, float angle)
{
	const float	rad = deg_to_radians(angle);
	const float	nx = vec->x * cos(rad) + vec->z * sin(rad);
	const float	nz = -vec->x * sin(rad) + vec->z * cos(rad);

	vec->x = nx;
	vec->z = nz;
}

void	rotatez_vec3d(t_vec3d *vec, float angle)
{
	const double	rad = deg_to_radians(angle);
	const float		nx = vec->x * cos(rad) - vec->y * sin(rad);
	const float		ny = vec->x * sin(rad) + vec->y * cos(rad);

	vec->x = nx;
	vec->y = ny;
}

void	rotatexyz_vec3d(t_vec3d *vec, float angle)
{
	rotatex_vec3d(vec, angle);
	rotatey_vec3d(vec, angle);
	rotatez_vec3d(vec, angle);
}
