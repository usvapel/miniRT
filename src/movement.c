
#include "minirt.h"

void movement(mlx_key_data_t keydata, t_engine *engine)
{
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			engine->camera.pos.z += 0.1;
		if (keydata.key == MLX_KEY_S)
			engine->camera.pos.z -= 0.1;
		if (keydata.key == MLX_KEY_D)
			engine->camera.pos.x += 0.1;
		if (keydata.key == MLX_KEY_C)
			engine->camera.pos.y -= 0.1;
		if (keydata.key == MLX_KEY_V)
			engine->camera.pos.y += 0.1;
		if (keydata.key == MLX_KEY_A)
			engine->camera.pos.x -= 0.1;
		update_viewport(&engine->viewport, engine->window);
		ft_memset(engine->image->pixels, 0, engine->window.width * engine->window.height * sizeof(int));
		color_background(engine);
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
