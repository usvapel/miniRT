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

	engine = get_engine();
	thread_cleanup();
	cleanup_data();
	mlx_terminate(engine->mlx);
	exit(1);
}

void	initialize_mlx(t_engine *engine)
{
	engine->mlx = mlx_init(800, 600, "miniRT | fps: 0", false);
	if (!engine->mlx)
		cleanup_and_exit();
	mlx_get_monitor_size(0, &engine->window.width, &engine->window.height);
	if (engine->window.width <= 0 || engine->window.height <= 0)
		cleanup_and_exit();
	mlx_terminate(engine->mlx);
	engine->window.aspect_ratio = (float)engine->window.width
		/ (float)engine->window.height;
	engine->mlx = mlx_init(engine->window.width, engine->window.height,
			"miniRT | fps: 0", true);
	if (!engine->mlx)
		cleanup_and_exit();
}

int	main(int ac, char **av)
{
	t_engine	*engine;

	if (ac < 2)
		return (0);
	engine = get_engine();
	input_parsing(engine, av);
	initialize_mlx(engine);
	setup_viewport();
	engine->image = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	engine->image_buffer = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	if (!engine->image || !engine->image_buffer)
		cleanup_and_exit();
	if (mlx_image_to_window(engine->mlx, engine->image, 0, 0) < 0)
		cleanup_and_exit();
	gettimeofday(&engine->frame.start, NULL);
	mlx_resize_hook(engine->mlx, resize_screen, engine);
	mlx_loop_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, draw_scene, engine);
	mlx_loop_hook(engine->mlx, fps_counter, engine);
	setup_threads(engine, true);
	mlx_loop(engine->mlx);
	cleanup_and_exit();
	return (0);
}
