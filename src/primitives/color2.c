#include "minirt.h"

uint32_t	color_to_int(t_color color)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	result;

	r = (uint8_t)(color.r);
	g = (uint8_t)(color.g);
	b = (uint8_t)(color.b);
	a = (uint8_t)(color.a);
	result = (r << 24) | (g << 16) | (b << 8) | a;
	return (result);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float	clamp(float value, float min, float max)
{
	if (value > max)
		value = max;
	if (value < min)
		value = min;
	return (value);
}

int	lerp(float level, int start, int end)
{
	return ((int)(start + level * (end - start)));
}

int	color_gradient(t_engine *engine, int y)
{
	float	r;
	float	g;
	float	b;
	float	level;
	int		color;

	level = (float)y / (float)(engine->window.height - 1);
	r = lerp(level, 135, 255);
	g = lerp(level, 206, 255);
	b = lerp(level, 250, 255);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	color = get_rgba((int)r, (int)g, (int)b, 255);
	return (color);
}
