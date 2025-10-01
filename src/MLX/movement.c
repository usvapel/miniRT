#include "MLX42.h"
#include "minirt.h"

void movement(t_engine *engine)
{
	move_camera(engine);
	engine->update = true;
	wait_for_threads();
	update_camera();
	engine->update = false;
	engine->recalculate = true;
}

void	key_hook(void *param)
{
	t_engine	*engine;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit();
	movement(engine);
}

// void mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
// {
// 	t_engine *engine = get_engine();
// 	(void)engine;
//     (void)mods;
//     (void)param;
//
//     if (action == MLX_PRESS)
//     {
//         if (button == MLX_MOUSE_BUTTON_LEFT)
// 		{
// 			move_object(engine);
// 		}
//
//     }
//     else if (action == MLX_RELEASE)
//     {
//         printf("Mouse button released\n");
//     }
// }

void cursor_hook(double x, double y, void *param)
{
	t_engine *engine = get_engine();
	(void )param;
	engine->mouse_x = x;
	engine->mouse_y = y;

	if (mlx_is_key_down(engine->mlx, MLX_KEY_C) && mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
		move_object(engine);
	else
		orient_camera(engine, x, y);
	// mlx_mouse_hook(engine->mlx, mouse_hook, NULL);
}
