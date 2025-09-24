
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

void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_engine *engine = get_engine();
	(void)engine;
    (void)mods;
    (void)param;

    if (action == MLX_PRESS)
    {
        if (button == MLX_MOUSE_BUTTON_LEFT)
            printf("Left click pressed\n");
        else if (button == MLX_MOUSE_BUTTON_RIGHT)
            printf("Right click pressed\n");
        else if (button == MLX_MOUSE_BUTTON_MIDDLE)
            printf("Middle click pressed\n");
    }
    else if (action == MLX_RELEASE)
    {
        printf("Mouse button released\n");
    }
}

void cursor_hook(double x, double y, void *param)
{
	t_engine *engine = get_engine();
	(void)param;

	printf("%f %f\n", x, y);
	mlx_mouse_hook(engine->mlx, mouse_hook, NULL);
}
