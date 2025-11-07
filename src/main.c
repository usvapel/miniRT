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
	get_screen_resolution(&engine->window.width, &engine->window.height);
	engine->window.aspect_ratio = (float)engine->window.width
		/ (float)engine->window.height;
	engine->mlx = mlx_init(engine->window.width, engine->window.height,
			"miniRT | fps: 0", true);
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
	mlx_image_to_window(engine->mlx, engine->image, 0, 0);
	engine->moving = false;
	gettimeofday(&engine->frame.start, NULL);
	setup_threads(engine);
	mlx_loop_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, draw_scene, engine);
	mlx_loop_hook(engine->mlx, fps_counter, engine);
	mlx_loop(engine->mlx);
	cleanup_and_exit();
	return (0);
}
