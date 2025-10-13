#include "minirt.h"
#include "primitives.h"

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

t_vec3d multiply_vec3d(t_vec3d one, t_vec3d two)
{
	t_vec3d new = {0};
	new.x = one.x * two.x;
	new.y = one.y * two.y;
	new.z = one.z * two.z;
	return new;
}

t_color vec3d_to_color(t_vec3d v) {
	t_color c;
	c.r = (unsigned char)(fmin(fmax(v.x, 0.0), 1.0) * 255.0);
	c.g = (unsigned char)(fmin(fmax(v.y, 0.0), 1.0) * 255.0);
	c.b = (unsigned char)(fmin(fmax(v.z, 0.0), 1.0) * 255.0);
	c.a = 255;
	return c;
}

t_vec3d color_to_vec3d(t_color c) {
	t_vec3d v;
	v.x = (float)c.r / 255.0f;
	v.y = (float)c.g / 255.0f;
	v.z = (float)c.b / 255.0f;
	return v;
}

t_vec3d reflect(t_vec3d direction, t_vec3d normal)
{
	float dot = dot_vec3d(direction, normal);
	t_vec3d tmp = nscale_vec3d(normal, dot);
	scale_vec3d(&tmp, 2);
	minus_vec3d(&direction, tmp);
	return direction;
}

void phong_model(t_hit *hit)
{
	if (hit->type == LIGHT)
		return ;
	t_engine *engine = get_engine();
	t_light *light = engine->objects->data[5];

	t_vec3d model_color = color_to_vec3d(hit->color);

	t_vec3d ambient = nscale_vec3d(model_color, 0.1);

	t_vec3d light_color = color_to_vec3d(light->color);

	t_vec3d light_dir = sub_vec3d(light->pos, hit->pos);
	normlize_vec3d(&light_dir);

	t_vec3d normal =  hit->normal;
	normlize_vec3d(&normal);

	// Diffuse
	float diffuse_strength = max(0.0, dot_vec3d(normal, light_dir));
	t_vec3d diffuse = nscale_vec3d(multiply_vec3d(light_color, model_color), diffuse_strength);

	// Specular
	t_vec3d view_dir = sub_vec3d(engine->camera.pos, hit->pos);
	normlize_vec3d(&view_dir);

	t_vec3d reflect_dir = reflect(nscale_vec3d(light_dir, -1.0f), normal);
	normlize_vec3d(&reflect_dir);

	float specular_strength = powf(max(0.0f, dot_vec3d(view_dir, reflect_dir)), 32.0f);
	t_vec3d specular = nscale_vec3d(light_color, specular_strength);

	if (hit->type == PLANE)
		scale_vec3d(&specular, 0.0f);
	// Final color
	t_vec3d final_color = add2_vec3d(ambient, add2_vec3d(diffuse, specular));

	hit->color = vec3d_to_color(final_color);
}

void	*raytracer(void *thread)
{
	t_engine *engine = get_engine();
	t_threads *t = thread;
	t_ray ray = {0};
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
				int type;
				i = 0;
				while (i < engine->object_count)
				{
					type = *(int *)(engine->objects->data[i]);
					// if (type == PLANE)
					// 	plane_hit(*((t_plane *)engine->objects->data[i]), ray, &hit);
					if (type == SPHERE)
						sphere_hit(*((t_sphere *)engine->objects->data[i]), ray, &hit);
					else if (type == CYLINDER)
						cylinder_hit(*((t_cylinder *)engine->objects->data[i]), ray, &hit);	
					else if (type == LIGHT)
						light_hit(*((t_light *)engine->objects->data[i]), ray, &hit);
					i++;
				}
				phong_model(&hit);
				i = 0;
				while (i < r_steps)
				{
					if (hit.prev_hit)
						mlx_put_pixel(engine->image_buffer, x, y, scale_color(&hit.color, 1));
					else
						mlx_put_pixel(engine->image_buffer, x, y, 255);
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
	normlize_vec3d(&ray.udir);
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
