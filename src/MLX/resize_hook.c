#include "minirt.h"

void	resize_screen(int window_width, int window_height, void *eng)
{
	t_engine	*engine;

	engine = (t_engine *)eng;
	engine->update = true;
	engine->moving = true;
	engine->window.width = window_width;
	engine->window.height = window_height;
	engine->window.aspect_ratio = (float)window_width / (float)window_height;
	wait_for_threads();
	update_viewport(&engine->viewport, engine->window);
	setup_threads(engine, false);
	if (!mlx_resize_image(engine->image, engine->window.width,
			engine->window.height))
		runtime_error("image resize failed");
	if (!mlx_resize_image(engine->image_buffer, engine->window.width,
			engine->window.height))
		runtime_error("image resize failed");
	if (engine->image == NULL || engine->image_buffer == NULL)
		runtime_error("image became NULL after resize");
	engine->lcamera = engine->camera;
	engine->update = false;
}
