
#include "minirt.h"

int scale_color(t_color *color, float brightness)
{
  int r = (int)(color->r * brightness);
  int g = (int)(color->g * brightness);
  int b = (int)(color->b * brightness);
  return (r << 16 | g << 8 | b);
}

int get_color(t_color *color)
{
	return (color->r << 24 | color->g << 16 | color->b << 8 | color->a);
}

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

int clamp(int value, int min, int max)
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
	int r;
	int g;
	int b;
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
