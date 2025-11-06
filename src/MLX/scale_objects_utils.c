#include "minirt.h"

void	scale_cube(t_cube *cube, float dx, float dy, float dt)
{
	cube->w += OBJ_S_SPEED * -dx * dt;
	cube->h += OBJ_S_SPEED * dy * dt;
	if (cube->h <= 0.05f)
		cube->h = 0.05f;
	if (cube->w <= 0.05f)
		cube->w = 0.05f;
}

void	scale_paraboloid(t_paraboloid *para, float dx, float dy, float dt)
{
	para->focal += OBJ_S_SPEED * -dx * dt;
	para->h += OBJ_S_SPEED * dy * dt;
	if (para->focal <= 0.05f)
		para->focal = 0.05f;
	if (para->h <= 0.05f)
		para->h = 0.05f;
}

void	scale_cylinder(t_cylinder *cy, float dx, float dy, float dt)
{
	cy->r += OBJ_S_SPEED * -dx * dt;
	cy->h += OBJ_S_SPEED * dy * dt;
	if (cy->r <= 0.05f)
		cy->r = 0.05f;
	if (cy->h <= 0.05f)
		cy->h = 0.05f;
}

void	scale_sphere(t_sphere *sphere, float dx, float dt)
{
	sphere->r += OBJ_S_SPEED * -dx * dt;
	if (sphere->r <= 0.05f)
		sphere->r = 0.05f;
}
