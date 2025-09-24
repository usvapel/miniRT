
#include "minirt.h"

void movement(mlx_key_data_t keydata, t_engine *engine)
{
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			engine->camera.pos.z += 100;
		if (keydata.key == MLX_KEY_S)
			engine->camera.pos.x += 10;
		if (keydata.key == MLX_KEY_A)
			engine->camera.pos.y += 10;
		if (keydata.key == MLX_KEY_D)
			engine->camera.pos.z -= 10;
		if (keydata.key == MLX_KEY_C)
			engine->camera.pos.z -= 10;
		if (keydata.key == MLX_KEY_V)
			engine->camera.pos.z -= 10;
		update_viewport(&engine->viewport, *(t_window *)engine->mlx->window);
		mlx_image_to_window(engine->mlx, engine->image, 0, 0);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (keydata.action == MLX_PRESS)
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(engine->mlx);
	movement(keydata, engine);
}
