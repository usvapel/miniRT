#include "minirt.h"

t_engine *get_engine()
{
	static t_engine engine;

	return (&engine);
}

void cleanup_and_exit()
{
	t_engine *engine;
	static bool cleanup_done = false;

	engine = get_engine();
	if (cleanup_done)
		exit(1);
	cleanup_done = true;
	thread_cleanup();
	free_vector(engine->objects);
	free_vector(engine->lights);
	mlx_close_window(engine->mlx);
	// mlx_terminate(engine->mlx);
	exit(1);
}

int	main(int ac, char **av)
{
	t_engine	*engine;

	if (ac < 2)
		return (0);
	engine = get_engine();
	input_parsing(engine, av);
	mlx_set_setting(MLX_HEADLESS, true);
	engine->mlx = mlx_init(10, 10, "miniRT | fps: 0", true);
    mlx_get_monitor_size(0, &engine->window.width, &engine->window.height);
	engine->window.aspect_ratio = (float)engine->window.width / engine->window.height;
	mlx_terminate(engine->mlx);
	setup_viewport();
	mlx_set_setting(MLX_HEADLESS, false);
	engine->mlx = mlx_init(engine->window.width, engine->window.height, "miniRT | fps: 0", true);
	engine->image = mlx_new_image(engine->mlx, engine->window.width, engine->window.height);
	engine->image_buffer = mlx_new_image(engine->mlx, engine->window.width, engine->window.height);
	engine->moving = false;
	mlx_image_to_window(engine->mlx, engine->image, 0, 0);
	gettimeofday(&engine->start, NULL);
	setup_threads(engine);
	mlx_loop_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, draw_scene, engine);
	mlx_loop_hook(engine->mlx, fps_counter, engine);
	mlx_loop(engine->mlx);
	cleanup_and_exit();
	// mlx_terminate(engine->mlx);
	return (0);
}
