
#include "minirt.h"

uint32_t scale_color(t_color *color, float brightness)
{
	uint8_t r = (uint8_t)(color->r * brightness);
	uint8_t g = (uint8_t)(color->g * brightness);
	uint8_t b = (uint8_t)(color->b * brightness);
	uint8_t a = (uint8_t)(color->a);
	uint32_t result = (r << 24) | (g << 16) | (b << 8) | a;
	return result;
}

// float get_color(t_color *color)
// {
// 	return (color->r << 24 | color->g << 16 | color->b << 8 | color->a);
// }

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int get_r(int rgba)
{
    return ((rgba >> 24) & 0xFF);
}

int get_g(int rgba)
{
    return ((rgba >> 16) & 0xFF);
}

int get_b(int rgba)
{
    return ((rgba >> 8) & 0xFF);
}

int get_a(int rgba)
{
    return (rgba & 0xFF);
}

float clamp(float value, float min, float max)
{
	if (value > max)
		value = max;
	if (value < min)
		value = min;
	return (value);
}

// linear interpolation
int lerp(float level, int start, int end)
{
	return (int)((1.0f - level) * start + level * end);
}

void calculate_gradient(t_engine *engine, int *color, int y)
{
	float r;
	float g;
	float b;
	float level;

	level = (float)y / (float)(engine->window.height - 1);
	r = lerp(level, 255, 127);
	g = lerp(level, 255, 179);
	b = lerp(level, 255, 255);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	*color = get_rgba(r, g, b, 255);
}

void color_background(t_engine *engine)
{
	int x;
	int y;
	int color;

	x = 0;
	while (x < engine->window.width)
	{
		y = 0;
		while (y < engine->window.height)
		{
			calculate_gradient(engine, &color, y);
			mlx_put_pixel(engine->image, x, y, color);
			y++;
		}
		x++;
	}
}
