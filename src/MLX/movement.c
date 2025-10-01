#include "minirt.h"

void movement(t_engine *engine)
{
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		engine->camera.pos.z += 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
		engine->camera.pos.z -= 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
		engine->camera.pos.x += 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_C))
		engine->camera.pos.y -= 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_V))
		engine->camera.pos.y += 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
		engine->camera.pos.x -= 0.1;
	else
		return ;
	engine->update = true;
	wait_for_threads();
	update_viewport(&engine->viewport, engine->window);
	engine->update = false;
	engine->recalculate = true;
	// engine->recalculate = false;
	// color_background(engine);
}

void movement(mlx_key_data_t keydata, t_engine *engine)
{
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		move_camera(keydata, engine);
	
		update_viewport(&engine->viewport, engine->window);
		engine->recalculate = true;
		wait_for_threads();
		mlx_image_t *tmp = engine->image;
		engine->image->pixels = engine->image_buffer->pixels;
		engine->image_buffer = tmp;
		engine->recalculate = false;
		// color_background(engine);
	}
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit();
	movement(engine);
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
	(void)y;
	(void)x;

	// printf("%f %f\n", x, y);
	mlx_mouse_hook(engine->mlx, mouse_hook, NULL);
}
