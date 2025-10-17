#include "minirt.h"

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
	engine->recalculate = !engine->complete_img;
	engine->moving = false;
}

inline float smoothstep( float x )
{
  return x*x*x/(3.0*x*x-3.0*x+1.0);
}

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
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
		else if (type == PARABOLOID)
			paraboloid_hit(*((t_paraboloid *)engine->objects->data[i]), *ray, hit);
		i++;
	}
	return (type);
}

static float	get_sample(int value, t_threads *t, int axis)
{
	float	result = value + t->block_size / 2.0f;
	if (result >= t->end_x && axis == X_AXIS)
		result = t->end_x - 1;
	if (result >= t->end_y && axis == Y_AXIS)
		result = t->end_y - 1;
	return (result);
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

bool color_in_range(t_color one, t_color two)
{
	float threshold = 0.05f;
	float distance = sqrtf(powf(one.r - two.r, 2) + 
						 powf(one.g - two.g, 2) + 
						 powf(one.b - two.b, 2));
	return distance <= threshold;
}

# define SAMPLE_SIZE 14

static void	calculate_scene(t_threads *t, t_engine *engine)
{
	t_ray	ray;
	t_hit	hit;
	float	x;
	float	y;

	y = t->start_y;
	while (y < t->end_y)
	{
		x = t->start_x;
		while (x < t->end_x)
		{
			t_color final_color = {0};
			t_color prev_sample = {0};
			t_color current_sample = {0};
			int similar;
			int sample_count = 0;
			int samples_taken = 1;
			while (sample_count < SAMPLE_SIZE)
			{
				float jx = (sample_count % 2) * 0.5f + float_rand(-0.25f, 0.25f);
				float jy = (sample_count / 2) * 0.5f + float_rand(-0.25f, 0.25f);
				float sx = x + jx;
				float sy = y + jy;
				ray = get_ray(get_sample(sx, t, X_AXIS), get_sample(sy, t, Y_AXIS));
				hit.prev_hit = false;
				object_intersection(engine, &ray, &hit);
				if (hit.prev_hit)
				{
					phong_model(engine, &hit);
					current_sample = hit.color;
					final_color.r += hit.color.r;
					final_color.g += hit.color.g;
					final_color.b += hit.color.b;
					final_color.a = 255;
					samples_taken++;
				}
				else
					final_color = int_to_color(final_color, color_gradient(engine, sy));
				if (samples_taken > 0 && color_in_range(current_sample, prev_sample))
				{
					similar++;
					if (similar >= 2)
						break ;
				}
				else
					similar = 0;
				prev_sample = current_sample;
				sample_count++;
			}
			final_color.r /= samples_taken;
			final_color.g /= samples_taken;
			final_color.b /= samples_taken;
			draw_to_buffer(t, x, y, scale_color(&final_color, 1));
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
		if (engine->moving)
			t->block_size = BLOCK_SIZE;
		t->done = false;
		t->last_move = timer(engine->last_move_time, 1);
		calculate_scene(t, engine);
		if (engine->moving == false && t->last_move == true && t->block_size > 1)
			t->block_size--;
		engine->complete_img = t->block_size == 1;
		t->done = true;
		engine->recalculate = false;
	}
	return (NULL);
}
