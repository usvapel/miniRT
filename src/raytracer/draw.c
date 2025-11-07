#include "minirt.h"

void	draw_scene(void *eng)
{
	t_engine		*engine;
	int				i;
	static uint8_t	*original_image_pixels = NULL;
	uint8_t			*temp;

	i = 0;
	engine = eng;
	if (original_image_pixels == NULL)
		original_image_pixels = engine->image->pixels;
	usleep(1000);
	wait_for_threads();
	while (engine->update == true)
		usleep(10);
	temp = original_image_pixels;
	engine->image->pixels = engine->image_buffer->pixels;
	engine->image_buffer->pixels = temp;
	original_image_pixels = engine->image->pixels;
	engine->frame.delta = time_in_ms() - engine->frame.t_last_frame;
	engine->frame.t_last_frame = time_in_ms();
	engine->frame.fps++;
	engine->recalculate = should_recalculate(engine);
	while (engine->moving && i < THREAD_COUNT)
		engine->threads[i++].block_size = PIXEL_BLOCK_SIZE;
	engine->moving = false;
}

void	draw_to_buffer(t_threads *t, int x, int y, int color)
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
