#include "minirt.h"

t_engine	*get_engine(void)
{
	static t_engine	engine;

	return (&engine);
}
t_object	*get_base_object(void *obj)
{
	return ((t_object *)obj);
}

void	cleanup_and_exit(void)
{
	t_engine	*engine;
	static bool	cleanup_done = false;

	engine = get_engine();
	if (cleanup_done)
		exit(1);
	cleanup_done = true;
	thread_cleanup();
	free_vector(engine->objects);
	free_vector(engine->lights);
	mlx_close_window(engine->mlx);
	exit(1);
}

void	get_screen_size(t_engine *engine)
{
	mlx_set_setting(MLX_HEADLESS, true);
	engine->mlx = mlx_init(10, 10, "init", true);
	mlx_get_monitor_size(0, &engine->window.width, &engine->window.height);
	engine->window.aspect_ratio = (float)engine->window.width
		/ engine->window.height;
	setup_viewport();
	mlx_set_setting(MLX_HEADLESS, false);
}

int	main(int ac, char **av)
{
	t_engine	*engine;

	if (ac != 2)
		return (0);
	engine = get_engine();
	input_parsing(engine, av);
	get_screen_size(engine);
	engine->mlx = mlx_init(engine->window.width, engine->window.height,
			"miniRT | fps: 0", true);
	engine->image = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	engine->image_buffer = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	engine->moving = false;
	mlx_image_to_window(engine->mlx, engine->image, 0, 0);
	gettimeofday(&engine->frame.start, NULL);
	setup_threads(engine);
	mlx_loop_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, draw_scene, engine);
	mlx_loop_hook(engine->mlx, fps_counter, engine);
	mlx_loop(engine->mlx);
	cleanup_and_exit();
	mlx_terminate(engine->mlx);
	return (0);
}
