#include "minirt.h"

static void	set_cube_min_max(t_cube *cube);

float	compute_axis_tbounds(t_cube cube, t_ray ray, int index, bool max)
{
	const float	origin = ((float *)&ray.origin)[index];
	const float	dir = ((float *)&ray.udir)[index];
	const float	min_b = ((float *)&cube.min)[index];
	const float	max_b = ((float *)&cube.max)[index];

	if (max)
		return ((max_b - origin) / dir);
	return ((min_b - origin) / dir);
}

void	swap_vals(float *val1, float *val2)
{
	float	tmp;

	tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}

void	set_min_max_tbounds(float *t1, float *t2, float *tmin, float *tmax)
{
	if (*t1 > *t2)
		swap_vals(t1, t2);
	if (*t1 > *tmin)
		*tmin = *t1;
	if (*t2 < *tmax)
		*tmax = *t2;
}

static void	set_cube_min_max(t_cube *cube)
{
	const t_vec3d	u = new_vec3d(cube->w, 0, 0);
	const t_vec3d	v = new_vec3d(0, cube->h, 0);
	const t_vec3d	z = new_vec3d(0, 0, cube->d);

	cube->min = add2_vec3d(cube->base.pos, nscale_vec3d(u, -0.5));
	cube->min = add2_vec3d(cube->min, nscale_vec3d(v, -0.5));
	cube->min = add2_vec3d(cube->min, nscale_vec3d(z, -0.5));
	cube->max = add2_vec3d(cube->base.pos, u);
	cube->max = add2_vec3d(cube->max, v);
	cube->max = add2_vec3d(cube->max, z);
}

t_cube	new_cube(float h, float w, float d)
{
	t_cube	cube;

	cube = (t_cube){0};
	cube.h = h;
	cube.w = w;
	cube.d = d;
	set_cube_min_max(&cube);
	return (cube);
}
