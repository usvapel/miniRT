#include "minirt.h"

int	main(int ac, char **av)
{
	t_engine	*engine;

	if (ac < 2)
		return (0);
	engine = get_engine();
	input_parsing(engine, av);
	initialize_mlx(engine);
	setup_viewport();
	mlx_resize_hook(engine->mlx, resize_screen, engine);
	mlx_loop_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, draw_scene, engine);
	mlx_loop_hook(engine->mlx, fps_counter, engine);
	setup_threads(engine, true);
	mlx_loop(engine->mlx);
	cleanup_and_exit();
	return (0);
}
