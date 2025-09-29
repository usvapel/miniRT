#include "minirt.h"

t_ray    get_ray(int x, int y);

void	setup_threads(void *eng)
{
    t_engine *engine = (t_engine *)eng;
	int y_step = engine->window.height / THREAD_COUNT;
	int x_step = engine->window.width;
	engine->recalculate = true;
	int i = 0;
	while (i < THREAD_COUNT)
	{
		engine->threads[i].index = i;
		engine->threads[i].start_y = y_step * i;
		engine->threads[i].end_y = y_step * (i + 1);
		engine->threads[i].start_x = 0;
		engine->threads[i].end_x = x_step;
		pthread_create(&engine->threads[i].thread, NULL, raytracer, &engine->threads[i]);
		i++;
	}
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
					mlx_put_pixel(engine->image, x, y, scale_color(&hit.color, 1));
				else
					mlx_put_pixel(engine->image, x, y, 0);
				x++;
			}
			y++;
		}
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
