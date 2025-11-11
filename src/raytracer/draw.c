#include "minirt.h"

void	thread_recalculate(t_engine *engine);
void	reset_pixel_block_size(t_engine *engine);

void	draw_scene(void *eng)
{
	t_engine	*engine;

	engine = eng;
	usleep(1000);
	wait_for_threads();
	while (engine->update)
		usleep(20);
	ft_memcpy(engine->image->pixels, engine->image_buffer->pixels,
		engine->window.width * engine->window.height * 4);
	engine->frame.delta = time_in_ms() - engine->frame.t_last_frame;
	engine->frame.t_last_frame = time_in_ms();
	engine->frame.fps++;
	engine->recalculate = should_recalculate(engine) || engine->moving;
	if (engine->moving)
		reset_pixel_block_size(engine);
	if (engine->recalculate)
		thread_recalculate(engine);
	engine->moving = false;
}

void	draw_to_buffer(t_threads *t, int x, int y, int color)
{
	const t_engine	*engine = get_engine();
	int				block_end_x;
	int				block_end_y;
	int				init_x;

	if (t->block_size <= 2)
	{
		mlx_put_pixel(engine->image_buffer, x, y, color);
		return ;
	}
	init_x = x;
	block_end_x = clamp(x + t->block_size, t->start_x, t->end_x);
	block_end_y = clamp(y + t->block_size, t->start_y, t->end_y);
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

void	reset_pixel_block_size(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		engine->threads[i].block_size = PIXEL_BLOCK_SIZE;
		i++;
	}
}

void	thread_recalculate(t_engine *engine)
{
	int	i;

	i = 0;
	while (i < THREAD_COUNT)
		engine->threads[i++].done = false;
}
