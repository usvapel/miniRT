#include "minirt.h"

uint32_t	color_to_int(t_color color)
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
	uint32_t	result;

	r = (uint8_t)(clamp(color.r, 0.0f, 255.0f));
	g = (uint8_t)(clamp(color.g, 0.0f, 255.0f));
	b = (uint8_t)(clamp(color.b, 0.0f, 255.0f));
	a = (uint8_t)(clamp(color.a, 0.0f, 255.0f));
	result = ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | a;
	return (result);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | a);
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
