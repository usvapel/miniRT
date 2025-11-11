#include "minirt.h"

void	initialize_mlx(t_engine *engine)
{
	engine->mlx = mlx_init(800, 600, "miniRT | fps: 0", false);
	if (!engine->mlx)
		cleanup_and_exit();
	mlx_get_monitor_size(0, &engine->window.width, &engine->window.height);
	if (engine->window.width <= 0 || engine->window.height <= 0)
		cleanup_and_exit();
	mlx_set_window_size(engine->mlx, engine->window.width,
		engine->window.height);
	engine->window.aspect_ratio = (float)engine->window.width
		/ (float)engine->window.height;
	mlx_terminate(engine->mlx);
	engine->mlx = mlx_init(engine->window.width, engine->window.height,
			"miniRT | fps: 0", true);
	if (!engine->mlx)
		cleanup_and_exit();
	engine->image = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	engine->image_buffer = mlx_new_image(engine->mlx, engine->window.width,
			engine->window.height);
	if (!engine->image || !engine->image_buffer)
		cleanup_and_exit();
	if (mlx_image_to_window(engine->mlx, engine->image, 0, 0) < 0)
		cleanup_and_exit();
	gettimeofday(&engine->frame.start, NULL);
}
