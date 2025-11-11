#include "minirt.h"

t_color	trace_ray(t_threads *t, t_ray ray, int depth)
{
	t_refract	rf;
	t_hit		hit;
	float		reflectance;
	float		indice;

	hit.prev_hit = false;
	(void)objects_intersection(get_engine(), &ray, &hit);
	if (!hit.prev_hit)
		return (skycolor(&ray, t->y));
	apply_texture(&hit);
	phong_model(get_engine(), &hit);
	reflectance = get_base_object(hit.obj)->material.reflect;
	indice = get_base_object(hit.obj)->material.refract;
	t->depth = depth;
	if (t->depth >= BOUNCES)
		return (skycolor(&ray, t->y));
	if (reflectance == -1 && indice == -1)
		return (hit.color);
	rf.reflectance = reflectance;
	rf.indice = indice;
	if (indice != -1)
		return (handle_refraction(t, &rf, ray, &hit));
	return (handle_reflection(t, ray, &hit, reflectance));
}

inline static float	get_sample(int value, t_threads *t, int axis)
{
	float	result;

	result = value + t->block_size / 2.0f;
	if (result >= t->end_x && axis == X_AXIS)
		result = t->end_x - 1;
	if (result >= t->end_y && axis == Y_AXIS)
		result = t->end_y - 1;
	return (result);
}

static void	calculate_scene(t_threads *t)
{
	t_ray	ray;
	int		x;
	int		y;
	t_color	final_color;

	y = t->start_y;
	while (y < t->end_y)
	{
		x = t->start_x;
		while (x < t->end_x)
		{
			ray = get_ray(get_sample(x, t, X_AXIS), get_sample(y, t, Y_AXIS));
			t->depth = 0;
			t->y = y;
			final_color = trace_ray(t, ray, t->depth);
			draw_to_buffer(t, x, y, color_to_int(final_color));
			x = clamp(x + t->block_size, t->start_x, t->end_x);
		}
		y = clamp(y + t->block_size, t->start_y, t->end_y);
	}
}

void	*raytracer(void *thread)
{
	t_engine	*engine;
	t_threads	*t;

	engine = get_engine();
	t = thread;
	t->done = true;
	if (!wait_for_threads())
		return (NULL);
	while (!t->end)
	{
		while (t->done && !t->end)
			usleep(10);
		if (t->end)
			return (NULL);
		t->last_move = timer(engine->last_move_time, QUALITY_DELAY_SECONDS);
		calculate_scene(t);
		if (!engine->moving && t->last_move && t->block_size > 0)
			t->block_size--;
		t->done = true;
	}
	return (NULL);
}
