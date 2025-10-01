#include "minirt.h"

void thread_cleanup()
{
	t_engine *engine = get_engine();
	int i = 0;
	while (i < THREAD_COUNT)
	{
		pthread_join(engine->threads[i].thread, NULL);
		i++;
	}
}

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
