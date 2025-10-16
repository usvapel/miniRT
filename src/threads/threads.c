#include "minirt.h"

void thread_cleanup()
{
	t_engine	*engine;
	int			i;

	engine = get_engine();
	i = 0;
	while (i < THREAD_COUNT)
	{
		engine->threads[i].end = true;
		i++;
	}
	i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(engine->threads[i].thread, NULL);
		i++;
	}
}

void	setup_threads(void *eng)
{
    t_engine	*engine;
	int			y_step;
	int			x_step;
	int			i;

	engine = eng;
	y_step = engine->window.height / THREAD_COUNT;
	x_step = engine->window.width;
	engine->recalculate = true;
	i = 0;
	while (i < THREAD_COUNT)
	{
		engine->threads[i].index = i;
		engine->threads[i].start_y = y_step * i;
		engine->threads[i].end_y = y_step * (i + 1);
		engine->threads[i].start_x = 0;
		engine->threads[i].end_x = x_step;
		engine->threads[i].done = false;
		engine->threads[i].end = false;
		engine->threads[i].block_size = 10;
		engine->threads[i].last_move = 0;
		pthread_create(&engine->threads[i].thread, NULL, raytracer, &engine->threads[i]);
		i++;
	}
}
