#include "minirt.h"

static bool orient_camera(t_engine *engine, float dx, float dy);
static void    look_up_down(t_camera *camera, float dy);
static void    move_left_right(t_camera *cam, int dir);
static bool    move_camera(t_engine *engine);

static bool    move_camera(t_engine *engine)
{
    t_camera *camera = &engine->camera;
    t_vec3d tmp = camera->dir;
	float dy;
	float dx;
	bool moved;

	dy = engine->mouse.prev_pos.y - engine->mouse.pos.y;
	dx = engine->mouse.prev_pos.x - engine->mouse.pos.x;
    scale_vec3d(&tmp, CAM_SPEED * engine->frame.delta);
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
		engine->camera.pos.y += CAM_SPEED * engine->frame.delta;
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT_CONTROL))
		engine->camera.pos.y -= CAM_SPEED * engine->frame.delta;
	else if (!moved)
		return false;
	return true;
}

static void    move_left_right(t_camera *cam, int dir)
{
    t_vec3d norm;
    float dz = cam->dir.z;
    float dx = cam->dir.x;
    long delta = get_engine()->frame.delta;
    norm.y = 0;
    norm.x = -dz;
    norm.z = dx;
    if (dir == LEFT)
        scale_vec3d(&norm, CAM_SPEED * delta);
    else
        scale_vec3d(&norm, -CAM_SPEED * delta);
    add_vec3d(&cam->pos, norm);
}

static void    look_up_down(t_camera *camera, float dy)
{
    t_vec3d tmp;
    float dt = get_engine()->frame.delta;
    tmp = camera->v;
    scale_vec3d(&tmp, -dy * CAM_SENS * dt);
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
	engine->last_move_time = get_seconds(engine);
	engine->recalculate = true;
}

static bool orient_camera(t_engine *engine, float dx, float dy)
{
    float dt = get_engine()->frame.delta;
    if (!mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
		return false;
    rotateY_vec3d(&engine->camera.dir, CAM_SENS * -dx * dt);
    // rotateX_vec3d(&engine->camera.dir, CAM_SENS * dy * dt);
    look_up_down(&engine->camera, CAM_SENS * dy * dt * 0.1);
	return true;
}

void handle_cam_movement(t_engine *engine)
{
	if (!move_camera(engine))
		return ;
	wait_for_threads();
	update_camera();
}