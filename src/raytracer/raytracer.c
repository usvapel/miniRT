#include "minirt.h"

bool should_recalculate(t_engine *eng);

void	draw_scene(void *eng)
{
	t_engine	*engine;
	int			i;

	i = 0;
	engine = eng;
	usleep(1000);
	wait_for_threads();
	while (engine->update == true)
		usleep(10);
	engine->image->pixels = engine->image_buffer->pixels;
	engine->frame.delta = time_in_ms() - engine->frame.t_last_frame;
	engine->frame.t_last_frame = time_in_ms();
	engine->frame.fps++;
	engine->recalculate = should_recalculate(engine);
	while (engine->moving && i < THREAD_COUNT)
		engine->threads[i++].block_size = PIXEL_BLOCK_SIZE;
	engine->moving = false;
}

bool should_recalculate(t_engine *eng)
{
	int i;

	i = 0;
	if (eng->moving)
		return true;
	while (i < THREAD_COUNT)	
	{
		if (eng->threads[i++].block_size != 1)
			return true;
	}
	return false;
}

bool obj_intersection(void *obj, t_ray ray, t_hit *hit)
{
	t_object *base = (t_object *)obj;
	int type = base->type;

	if (type == PLANE)
		return plane_hit(((t_plane *)obj), ray, hit);
	if (type == SPHERE)
		return sphere_hit(((t_sphere *)obj), ray, hit);
	else if (type == CYLINDER)
		return cylinder_hit(((t_cylinder *)obj), ray, hit);	
	else if (type == LIGHT)
		return light_hit(((t_generic_light *)obj), ray, hit);
	else if (type == PARABOLOID)
		return paraboloid_hit(((t_paraboloid *)obj), ray, hit);
	else
		return false;
}

int	objects_intersection(t_engine *engine, t_ray *ray, t_hit *hit)
{
	int	i;

	i = 0;
	while (i < engine->objects->count)
	{
		obj_intersection(engine->objects->data[i], *ray, hit);
		i++;
	}
	if (hit->prev_hit)
		apply_texture(hit);
	return (hit->type);
}

static void	draw_to_buffer(t_threads *t, int x, int y, int color)
{
	const t_engine	*engine = get_engine();
	int				block_end_x;
	int				block_end_y;
	int				init_x;

	init_x = x;
	if (y + t->block_size > t->end_y)
		block_end_y = t->end_y;
	else
		block_end_y = y + t->block_size;
	if (x + t->block_size > t->end_x)
		block_end_x = t->end_x;
	else
		block_end_x = x + t->block_size;
	while (y < block_end_y)
	{
		x = init_x;
		while (x < block_end_x)
		{
			mlx_put_pixel(engine->image_buffer, x, y, color);
			x++;
		}
		y++;
	}
}

t_color trace_ray(t_ray ray, int depth, int y)
{
	t_refract rf = {0};
	t_hit	hit;
	float	reflectance;
	float	indice;

	hit.prev_hit = false;
	(void)objects_intersection(get_engine(), &ray, &hit);
	if (!hit.prev_hit)
		return (int_to_color(color_gradient(get_engine(), y)));
	phong_model(get_engine(), &hit);
	reflectance = ((t_object *)hit.obj)->material.reflect;
	indice = ((t_object *)hit.obj)->material.refract;
	if (depth >= BOUNCES || reflectance == 0)
		return (hit.color);
	rf.reflectance = reflectance;
	rf.indice = indice;
	if (indice > 1.0f)
		return (handle_refraction(&rf, ray, &hit, depth, y));
	return (handle_reflection(ray, &hit, reflectance, depth, y));
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

	y = t->start_y;
	while (y < t->end_y)
	{
		x = t->start_x;
		while (x < t->end_x)
		{
			ray = get_ray(get_sample(x, t, X_AXIS), get_sample(y, t, Y_AXIS));
			draw_to_buffer(t, x, y, color_to_int(trace_ray(ray, 0, y)));
			x += t->block_size;
		}
		y += t->block_size;
	}
}

void	*raytracer(void *thread)
{
	t_engine	*engine;
	t_threads	*t;

	engine = get_engine();
	t = thread;
	t->done = true;
	wait_for_threads();
	while (!t->end)
	{
		while (engine->recalculate == false)
		{
			if (t->end)
				return (NULL);
			usleep(10);
		}
		t->done = false;
		t->last_move = timer(engine->last_move_time, 1);
		calculate_scene(t);
		if (engine->moving == false && t->last_move == true && t->block_size > 1)
			t->block_size--;
		t->done = true;
		engine->recalculate = false;
	}
	return (NULL);
}
