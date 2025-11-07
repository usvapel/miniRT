#include "minirt.h"

void	thread_cleanup(void)
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

static void	init_values(t_engine *engine, int i, int x_step, int y_step)
{
	engine->threads[i].index = i;
	engine->threads[i].start_y = y_step * i;
	engine->threads[i].end_y = y_step * (i + 1);
	engine->threads[i].start_x = 0;
	engine->threads[i].end_x = x_step;
	engine->threads[i].done = false;
	engine->threads[i].end = false;
	engine->threads[i].block_size = PIXEL_BLOCK_SIZE;
	engine->threads[i].last_move = 0;
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
		init_values(engine, i, x_step, y_step);
		if (pthread_create(&engine->threads[i].thread, NULL, raytracer,
				&engine->threads[i]))
		{
			engine->thread_failure = true;
			while (i)
				pthread_join(engine->threads[--i].thread, NULL);
			runtime_error("failure in thread creation");
		}
		i++;
	}
}

bool	should_recalculate(t_engine *eng)
{
	int	i;

	i = 0;
	if (eng->moving)
		return (true);
	while (i < THREAD_COUNT)
	{
		if (eng->threads[i++].block_size != 1)
			return (true);
	}
	return (false);
}

bool	wait_for_threads(void)
{
	t_engine	*engine;
	int			thread_finished;
	int			i;

	engine = get_engine();
	while (true)
	{
		thread_finished = 0;
		i = 0;
		while (i < THREAD_COUNT)
		{
			if (engine->thread_failure)
				return (false);
			if (engine->threads[i].done == true)
				thread_finished++;
			i++;
		}
		if (thread_finished == THREAD_COUNT)
			return (true);
		usleep(10);
	}
}
