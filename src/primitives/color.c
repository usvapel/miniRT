#include "minirt.h"

t_color	mix_colors(t_color c1, t_color c2, float r)
{
	c1.r = c1.r * (1 - r) + c2.r * r;
	c1.g = c1.g * (1 - r) + c2.g * r;
	c1.b = c1.b * (1 - r) + c2.b * r;
	c1.a = c1.a * (1 - r) + c2.a * r;
	if (c1.r > 255)
		c1.r = 255;
	if (c1.g > 255)
		c1.g = 255;
	if (c1.b > 255)
		c1.b = 255;
	if (c1.a > 255)
		c1.a = 255;
	return (c1);
}

t_color	vec3d_to_color(t_vec3d v)
{
	t_color	c;

	c.r = (unsigned char)(fmin(fmax(v.x, 0.0), 1.0) * 255.0);
	c.g = (unsigned char)(fmin(fmax(v.y, 0.0), 1.0) * 255.0);
	c.b = (unsigned char)(fmin(fmax(v.z, 0.0), 1.0) * 255.0);
	c.a = 255;
	return (c);
}

t_color	int_to_color(int c)
{
	t_color	result;

	result.r = (c >> 24) & 0xFF;
	result.g = (c >> 16) & 0xFF;
	result.b = (c >> 8) & 0xFF;
	result.a = c & 0xFF;
	return (result);
}

t_vec3d	color_to_vec3d(t_color c)
{
	t_vec3d	v;

	v.x = (float)c.r / 255.0f;
	v.y = (float)c.g / 255.0f;
	v.z = (float)c.b / 255.0f;
	return (v);
}

void	apply_color(t_color *color, float brightness)
{
	color->r = (color->r * brightness);
	color->g = (color->g * brightness);
	color->b = (color->b * brightness);
	color->a = (color->a);
}
