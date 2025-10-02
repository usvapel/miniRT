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
}

void	*raytracer(void *thread)
{
	t_engine *engine = get_engine();
	t_sphere *spheres = *engine->objects;
	t_plane *plane = engine->objects[1];
	t_threads *t = thread;
	t_ray ray;
	t_hit hit;
	int x;
	int y;
	while (true)
	{
		while (engine->recalculate == false)
			usleep(10);
		t->done = false;
		y = t->start_y;
		while (y < t->end_y)
		{
			x = t->start_x;
			while (x < t->end_x)
			{
				hit.prev_hit = false;
				ray = get_ray(x, y);
				plane_hit(*plane, ray, &hit);
				sphere_hit(spheres[0], ray, &hit);
				if (hit.prev_hit)
					mlx_put_pixel(engine->image_buffer, x, y, scale_color(&hit.color, 1));
				else
					mlx_put_pixel(engine->image_buffer, x, y, 0);
				x++;
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
