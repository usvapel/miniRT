#include "minirt.h"

void movement(t_engine *engine)
{
	if (!move_camera(engine))
		return ;
	wait_for_threads();
	update_camera();
}

void scale_objects(t_engine *engine)
{
	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		t_sphere *sphere = inside_object(engine->mouse.pos.x, engine->mouse.pos.y);
		if (!sphere)
			return ;
		scale_object(engine->mouse.pos.x, engine->mouse.pos.y);
		update_camera();
	}
}

void	key_hook(void *param)
{
	t_engine	*engine;
	int x; int y;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit();

	mlx_get_mouse_pos(engine->mlx, &x, &y);
	engine->mouse.prev_pos = engine->mouse.pos;
	engine->mouse.pos.x = x;
	engine->mouse.pos.y = y;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_C))
		scale_objects(engine);
	// else if (mlx_is_key_down(engine->mlx, MLX_KEY_X))
	// 	asdasd();
	// else if (mlx_is_key_down(engine->mlx, MLX_KEY_Z))
	// 	asdasd();
	else
		movement(engine);
}
