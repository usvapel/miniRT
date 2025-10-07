#include "minirt.h"

void    move_left_right(t_camera *cam, int dir);
void    look_up_down(t_camera *camera, float dy);

void    move_camera(t_engine *engine)
{
    t_camera *camera = &engine->camera;
    t_vec3d tmp = camera->dir;
    scale_vec3d(&tmp, 0.1);
    if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
        add_vec3d(&camera->pos, tmp);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
        minus_vec3d(&camera->pos, tmp);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
        move_left_right(camera, RIGHT);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
        move_left_right(camera, LEFT);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_V))
		engine->camera.pos.y += 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_C))
		engine->camera.pos.y -= 0.1;
}

void    move_left_right(t_camera *cam, int dir)
{
    t_vec3d norm;
    float dz = cam->dir.z;
    float dx = cam->dir.x;
    norm.y = 0;
    norm.x = -dz;
    norm.z = dx;
    if (dir == LEFT)
        scale_vec3d(&norm, 0.1);
    else
        scale_vec3d(&norm, -0.1);
    add_vec3d(&cam->pos, norm);
}

void    look_up_down(t_camera *camera, float dy)
{
    t_vec3d tmp;
    tmp = camera->v;
    scale_vec3d(&tmp, dy * 0.001);
    add_vec3d(&camera->dir, tmp);
    normlize_vec3d(&camera->dir);
}

void update_camera(void)
{
    t_engine *engine = get_engine();
    update_viewport(&engine->viewport, engine->window);
	engine->update = false;
	engine->moving = true;
	engine->last_move_time = get_seconds(engine);
	engine->recalculate = true;
}

void    orient_camera(t_engine *engine, float nx, float ny)
{
	static t_vec3d prev_pos;
	float dx = nx - prev_pos.x;
	float dy = ny - prev_pos.y;
	prev_pos.x = nx;
	prev_pos.y = ny;
    if (!mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
        return;
    rotateY_vec3d(&engine->camera.dir, 0.1 * dx);
    look_up_down(&engine->camera, dy);
    update_camera();
}
