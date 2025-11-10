#include "minirt.h"

void	update_camera(void)
{
	t_engine	*engine;

	engine = get_engine();
	engine->camera = engine->lcamera;
	update_viewport(&engine->viewport, engine->window);
}
