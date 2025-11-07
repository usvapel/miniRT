#include "minirt.h"

void	key_hook(void *param)
{
	t_engine	*engine;
	int			x;
	int			y;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
	{
		if (engine->autosave)
			autosave_scene();
		mlx_close_window(engine->mlx);
	}
	mlx_get_mouse_pos(engine->mlx, &x, &y);
	engine->mouse.prev_pos = engine->mouse.pos;
	engine->mouse.pos.x = x;
	engine->mouse.pos.y = y;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_C))
		scale_objects(engine);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_Z))
		move_objects(engine);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_X))
		rotate_objects(engine);
	else
		handle_cam_movement(engine);
}
