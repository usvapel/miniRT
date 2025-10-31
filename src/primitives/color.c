#include "minirt.h"

t_color mix_colors(t_color c1, t_color c2, float r)
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
	return c;
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

t_color int_to_color(int c)
{
	t_color result;
	result.r = get_r(c);
	result.g = get_g(c);
	result.b = get_b(c);
	result.a = get_a(c);
	return result;
}

t_vec3d color_to_vec3d(t_color c)
{
	t_vec3d v;
	v.x = (float)c.r / 255.0f;
	v.y = (float)c.g / 255.0f;
	v.z = (float)c.b / 255.0f;
	return v;
}

void apply_color(t_color *color, float brightness)
{
	color->r = (color->r * brightness);
	color->g = (color->g * brightness);
	color->b = (color->b * brightness);
	color->a = (color->a);
}

uint32_t color_to_int(t_color color)
{
	uint8_t r = (uint8_t)(color.r);
	uint8_t g = (uint8_t)(color.g);
	uint8_t b = (uint8_t)(color.b);
	uint8_t a = (uint8_t)(color.a);
	uint32_t result = (r << 24) | (g << 16) | (b << 8) | a;
	return result;
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

float clamp(float value, float min, float max)
{
	if (value > max)
		value = max;
	if (value < min)
		value = min;
	return (value);
}

int lerp(float level, int start, int end)
{
    return (int)(start + level * (end - start));
}

int color_gradient(t_engine *engine, int y)
{
	float r;
	float g;
	float b;
	float level;
	int color;

	level = (float)y / (float)(engine->window.height - 1);
	r = lerp(level, 135, 255);
	g = lerp(level, 206, 255);
	b = lerp(level, 250, 255);
	r = clamp(r, 0, 255);
	g = clamp(g, 0, 255);
	b = clamp(b, 0, 255);
	color = get_rgba((int)r, (int)g, (int)b, 255);
	return color;
}
