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
	(void )param;

	orient_camera(engine, x, y);
	mlx_mouse_hook(engine->mlx, mouse_hook, NULL);
}
