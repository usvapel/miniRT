#include "minirt.h"

void    move_left_right(t_camera *cam, int dir);
void    look_up_down(t_camera *camera, float dy);

bool    move_camera(t_engine *engine)
{
    t_camera *camera = &engine->camera;
    t_vec3d tmp = camera->dir;
	float dy;
	float dx;
	bool moved;

	dy = engine->mouse.prev_pos.y - engine->mouse.pos.y;
	dx = engine->mouse.prev_pos.x - engine->mouse.pos.x;
    scale_vec3d(&tmp, 0.1);
	moved = orient_camera(engine, dx, dy);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W))
		add_vec3d(&camera->pos, tmp);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_S))
        minus_vec3d(&camera->pos, tmp);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_D))
        move_left_right(camera, RIGHT);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_A))
        move_left_right(camera, LEFT);
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_SPACE))
		engine->camera.pos.y += 0.1;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT_CONTROL))
		engine->camera.pos.y -= 0.1;
	else if (!moved)
		return false;
	return true;
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

void    move_pos_left_right(t_camera *cam, t_vec3d *pos, float d)
{
    t_vec3d norm;
    float dz = cam->dir.z;
    float dx = cam->dir.x;
    norm.y = 0;
    norm.x = -dz;
    norm.z = dx;
    scale_vec3d(&norm, 0.001 * d);
    add_vec3d(pos, norm);
}


void    look_up_down(t_camera *camera, float dy)
{
    t_vec3d tmp;
    tmp = camera->v;
    scale_vec3d(&tmp, -dy * 0.001);
    add_vec3d(&camera->dir, tmp);
    normlize_vec3d(&camera->dir);
}

void update_camera(void)
{
    t_engine *engine = get_engine();
	engine->update = true;
    update_viewport(&engine->viewport, engine->window);
	engine->update = false;
	engine->moving = true;
	engine->recalculate = true;
}

bool    orient_camera(t_engine *engine, float dx, float dy)
{
    if (!mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
		return false;
    rotateY_vec3d(&engine->camera.dir, 0.1 * -dx);
    look_up_down(&engine->camera, dy);
	return true;
}
