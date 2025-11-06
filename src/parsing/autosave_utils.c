#include "minirt.h"

void	save_sphere(t_sphere s, t_object b)
{
	printf("sp  %.1f,%.1f,%.1f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y,
		b.pos.z, s.r + s.r, b.color.r, b.color.g, b.color.b);
	save_additional_vals(b);
}

void	save_cylinder(t_cylinder c, t_object b)
{
	printf("cy  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.1f  %.1f  %.0f,%.0f,%.0f  ",
		b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, c.r, c.h,
		b.color.r, b.color.g, b.color.b);
	save_additional_vals(b);
}

void	save_plane(t_plane p, t_object b)
{
	(void)p;
	printf("pl  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.0f,%.0f,%.0f  ", b.pos.x,
		b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, b.color.r, b.color.g,
		b.color.b);
	save_additional_vals(b);
}

void	save_paraboloid(t_paraboloid p, t_object b)
{
	printf("pa  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.1f  %.1f  %.0f,%.0f,%.0f  ",
		b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, p.focal,
		p.h, b.color.r, b.color.g, b.color.b);
	save_additional_vals(b);
}

void	save_cube(t_cube c, t_object b)
{
	printf("cu  %.1f,%.1f,%.1f  %.1f  %.1f  %.1f,%.1f,%.1f  %.0f,%.0f,%.0f  ",
		b.pos.x, b.pos.y, b.pos.z, c.w, c.h, b.axis->x, b.axis->y, b.axis->z,
		b.color.r, b.color.g, b.color.b);
	save_additional_vals(b);
}
