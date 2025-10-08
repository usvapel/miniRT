#include "minirt.h"

t_ray    get_ray(int x, int y);

void wait_for_threads()
{
	t_engine *engine = get_engine();
	int done_count;
	while (true)
	{
		done_count = 0;
		for (int i = 0; i < THREAD_COUNT; i++)
			if (engine->threads[i].done == true)
				done_count++;
		if (done_count == THREAD_COUNT)
			return;
		usleep(10);
	}
	engine->moving = false;
}

void	draw_scene(void *eng)
{
	t_engine *engine = eng;
	usleep(1000);
	wait_for_threads();
	while (engine->update == true)
		usleep(10);
	engine->image->pixels = engine->image_buffer->pixels;
	engine->fps++;
	engine->recalculate = true;
	engine->moving = false;
}

void	*raytracer(void *thread)
{
	t_engine *engine = get_engine();
	t_threads *t = thread;
	t_ray ray;
	t_hit hit = {0};
	int x;
	int y;
	int i = 0;
	bool last_move = false;
	int r_steps = 10;
	while (true)
	{
		while (engine->recalculate == false)
			usleep(10);
		t->done = false;
		last_move = timer(engine->last_move_time, 1);
		y = t->start_y;
		while (y < t->end_y)
		{
			x = t->start_x;
			while (x < t->end_x)
			{
				hit.prev_hit = false;
				ray = get_ray(x, y);
				plane_hit(*((t_plane *)engine->objects->data[4]), ray, &hit);
				i = 0;
				while (i < engine->object_count)
				{
					int type = *(int *)(engine->objects->data[i]);
					// if (type == PLANE)
					// 	plane_hit(*((t_plane *)engine->objects->data[i]), ray, &hit);
					if (type == SPHERE)
						sphere_hit(*((t_sphere *)engine->objects->data[i]), ray, &hit);
					if (type == CYLINDER)
						cylinder_hit(*((t_cylinder *)engine->objects->data[i]), ray, &hit);	
					if (type == LIGHT)
						light_hit(*((t_light *)engine->objects->data[i]), ray, &hit);
					i++;
				}
				i = 0;
				while (i < r_steps)
				{
					if (hit.prev_hit)
						mlx_put_pixel(engine->image_buffer, x, y, scale_color(&hit.color, 1));
					else
						mlx_put_pixel(engine->image_buffer, x, y, 0);
					x++;
					i++;
					if (engine->moving == false && last_move == true)
						if (r_steps > 1)
							r_steps--;
					if (r_steps == 1 && engine->moving == true)
						r_steps = 10;
				}
			}
			y++;
		}
		t->done = true;
		engine->recalculate = false;
	}
	return (NULL);
}

t_ray    get_ray(int x, int y)
{
    const t_engine *engine = get_engine();
    const t_vec3d pixel = get_viewport_pixel(x, y);
    t_ray ray;

    ray.origin = engine->camera.pos;
    ray.udir = pixel;
    minus_vec3d(&ray.udir, engine->camera.pos);
    return (ray);
}

t_vec3d get_point_on_ray(t_ray ray, float t)
{
    t_vec3d p;
    t_vec3d tmp;

    p = ray.origin;
    tmp = ray.udir;
    scale_vec3d(&tmp, t);
    add_vec3d(&p, tmp);
    return p;
}
