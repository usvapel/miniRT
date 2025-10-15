#include "minirt.h"

t_ray    get_ray(int x, int y);

void	wait_for_threads()
{
	t_engine	*engine = get_engine();
	int			thread_finished;
	int			i;

	while (true)
	{
		thread_finished = 0;
		i = 0;
		while (i < THREAD_COUNT)
		{
			if (engine->threads[i].done == true)
				thread_finished++;
			i++;
		}
		if (thread_finished == THREAD_COUNT)
			return;
		usleep(10);
	}
	engine->moving = false;
}

void	draw_scene(void *eng)
{
	t_engine	*engine;

	engine = eng;
	usleep(1000);
	wait_for_threads();
	while (engine->update == true)
		usleep(10);
	engine->image->pixels = engine->image_buffer->pixels;
	engine->fps++;
	engine->recalculate = true;
	engine->moving = false;
}

int	object_intersection(t_engine *engine, t_ray *ray, t_hit *hit)
{
	int	type;
	int	i;

	plane_hit(*((t_plane *)engine->objects->data[4]), *ray, hit);
	i = 0;
	while (i < engine->object_count)
	{
		type = *(int *)(engine->objects->data[i]);
		// if (type == PLANE)
		// 	plane_hit(*((t_plane *)engine->objects->data[i]), ray, &hit);
		if (type == SPHERE)
			sphere_hit(*((t_sphere *)engine->objects->data[i]), *ray, hit);
		else if (type == CYLINDER)
			cylinder_hit(*((t_cylinder *)engine->objects->data[i]), *ray, hit);	
		else if (type == LIGHT)
			light_hit(*((t_light *)engine->objects->data[i]), *ray, hit);
		i++;
	}
	return (type);
}

// float	random_float()
// {
// 	return (float)rand() / ((float)RAND_MAX + 1.0f);
// }

void	*raytracer(void *thread)
{
	t_engine	*engine;
	t_threads	*t;
	t_ray		ray = {0};
	t_hit		hit = {0};
	int			x;
	int			y;
	int color;
	float sample_x;
	float sample_y;
	int block_end_y;
	int block_end_x;
	int block_x;
	int block_y;
	int block_size = 10;
	bool last_move = false;
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
		last_move = timer(engine->last_move_time, 1);
		y = t->start_y;
		while (y < t->end_y)
		{
			x = t->start_x;
			while (x < t->end_x)
			{
				hit.prev_hit = false;
				sample_x = x + block_size / 2.0f;
				sample_y = y + block_size / 2.0f;
				if (sample_x >= t->end_x)
					sample_x = t->end_x - 1;
				if (sample_y >= t->end_y)
					sample_y = t->end_y - 1;
				ray = get_ray(sample_x, sample_y);
				(void)object_intersection(engine, &ray, &hit);
				phong_model(engine, &hit);
				if (hit.prev_hit)
					color = scale_color(&hit.color, 1);
				else
					color = color_gradient(engine, y);
				block_end_y = y + block_size;
				block_end_x = x + block_size;
				block_y = y - 1;
				while (++block_y < block_end_y)
				{
					block_x = x - 1;
					while (++block_x < block_end_x)
						mlx_put_pixel(engine->image_buffer, block_x, block_y, color);
				}
				x += block_size;
			}
			y += block_size;
		}
		if (engine->moving == false && last_move == true)
			if (block_size > 1)
				block_size--;
		if (block_size == 1 && engine->moving == true)
			block_size = 10;
		t->done = true;
		engine->recalculate = false;
	}
	return (NULL);
}

t_ray    get_ray(int x, int y)
{
    const t_engine	*engine = get_engine();
    const t_vec3d	pixel = get_viewport_pixel(x, y);
    t_ray			ray;

    ray.origin = engine->camera.pos;
    ray.udir = pixel;
    minus_vec3d(&ray.udir, engine->camera.pos);
	normlize_vec3d(&ray.udir);
    return (ray);
}

t_vec3d	get_point_on_ray(t_ray ray, float t)
{
    t_vec3d	p;
    t_vec3d	tmp;

    p = ray.origin;
    tmp = ray.udir;
    scale_vec3d(&tmp, t);
    add_vec3d(&p, tmp);
    return (p);
}
