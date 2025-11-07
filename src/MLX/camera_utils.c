#include "minirt.h"

void	update_camera(void)
{
	t_engine	*engine;

	engine = get_engine();
	engine->update = true;
	update_viewport(&engine->viewport, engine->window);
	engine->update = false;
	engine->moving = true;
	engine->last_move_time = get_seconds(engine);
	engine->recalculate = true;
}
