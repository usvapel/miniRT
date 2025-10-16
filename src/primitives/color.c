#include "minirt.h"

t_color	vec3d_to_color(t_vec3d v)
{
	t_color	c;
	c.r = (unsigned char)(fmin(fmax(v.x, 0.0), 1.0) * 255.0);
	c.g = (unsigned char)(fmin(fmax(v.y, 0.0), 1.0) * 255.0);
	c.b = (unsigned char)(fmin(fmax(v.z, 0.0), 1.0) * 255.0);
	c.a = 255;
	return c;
}

t_vec3d color_to_vec3d(t_color c)
{
	t_vec3d v;
	v.x = (float)c.r / 255.0f;
	v.y = (float)c.g / 255.0f;
	v.z = (float)c.b / 255.0f;
	return v;
}

t_color checker_board(t_hit *hit)
{
	float checker_size = 0.1f;
	t_color color1 = {225, 224, 220, 255};
	t_color color2 = {121, 121, 121, 255};
	t_color color3 = {0,0,0,0};

	int x = (int)floorf(hit->pos.x / checker_size);
	int z = (int)floorf(hit->pos.z / checker_size);

	t_color color = ((x + z) % 2 == 0) ? color1 : color2;
	if (x > 20 || z > 20 || x < -20 || z < -20)
		return color3;
	return (color);
}

void apply_color(t_color *color, float brightness)
{
	color->r = (color->r * brightness);
	color->g = (color->g * brightness);
	color->b = (color->b * brightness);
	color->a = (color->a);
}

uint32_t scale_color(t_color *color, float brightness)
{
	uint8_t r = (uint8_t)(color->r * brightness);
	uint8_t g = (uint8_t)(color->g * brightness);
	uint8_t b = (uint8_t)(color->b * brightness);
	uint8_t a = (uint8_t)(color->a);
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
