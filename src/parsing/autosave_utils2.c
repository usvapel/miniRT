#include "minirt.h"

void	save_texture(void *txt, t_texture_type type)
{
	t_image_text	*img;
	t_checker		*ch;

	if (type == IMAGE)
	{
		img = (t_image_text *)txt;
		printf("tx img %s", img->txt_source);
		if (img->bump_source)
			printf("  %s", img->bump_source);
		printf("\n");
	}
	else if (type == CHECKERBOARD)
	{
		ch = (t_checker *)txt;
		printf("tx ch %.0f,%.0f,%.0f  %.0f,%.0f,%.0f  %.1f\n", ch->color1.r,
			ch->color1.g, ch->color1.b, ch->color2.r, ch->color2.g,
			ch->color2.b, ch->block_size);
	}
}

void	save_camera(t_camera c)
{
	printf("# Camera\n");
	printf("C  %.2f,%.2f,%.2f  %.2f,%.2f,%.2f  %d\n", c.pos.x, c.pos.y, c.pos.z,
		c.dir.x, c.dir.y, c.dir.z, c.fov);
}

void	save_ampient(t_ambient a)
{
	printf("A  %.1f  %.0f,%.0f,%.0f\n", a.ratio, a.base.color.r, a.base.color.g,
		a.base.color.b);
}

void	save_light(t_generic_light l)
{
	const t_object	b = l.base;
	t_spot_light	s;

	if (b.type == POINT_LIGHT)
	{
		printf("L  %.2f,%.2f,%.2f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y,
			b.pos.z, l.brightness, b.color.r, b.color.g, b.color.b);
		if (l.obj_index >= 0)
			printf("obj %d\n", l.obj_index);
		else
			printf("\n");
	}
	if (b.type == SPOT_LIGHT)
	{
		s = l.spot_light;
		printf("LS  %.2f,%.2f,%.2f  %.2f,%.2f,%.2f  %.1f  %.1f  %.0f \
			%.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y,
			b.axis->z, l.brightness, s.range, s.fov, b.color.r, b.color.g,
			b.color.b);
		if (l.obj_index >= 0)
			printf("obj %d\n", l.obj_index);
		else
			printf("\n");
	}
}

void	save_additional_vals(t_object b)
{
	if (b.material.reflect > 0)
		printf("rl %1.f  ", b.material.reflect);
	if (b.material.refract > 0)
		printf("rf %1.f  ", b.material.refract);
	if (b.texture.index > -1 && b.texture.type == CHECKERBOARD)
		printf("ch %d", b.texture.index);
	if (b.texture.index > -1 && b.texture.type == IMAGE)
		printf("img %d", b.texture.index);
	printf("\n");
}
