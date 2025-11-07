#include "minirt.h"

static bool	orient_camera(t_engine *engine);
static void	look_up_down(t_camera *camera, float dy);
static void	move_left_right(t_camera *cam, int dir);
static bool	move_camera(t_engine *engine);

static bool	move_camera(t_engine *engine)
{
	t_camera	*camera;
	t_vec3d		tmp_dir;
	bool		oriented;

	camera = &engine->camera;
	tmp_dir = nscale_vec3d(camera->dir, CAM_SPEED * engine->frame.delta);
	oriented = orient_camera(engine);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_W) && ++oriented)
		add_vec3d(&camera->pos, tmp_dir);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_S) && ++oriented)
		minus_vec3d(&camera->pos, tmp_dir);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_D) && ++oriented)
		move_left_right(camera, RIGHT);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_A) && ++oriented)
		move_left_right(camera, LEFT);
	if (mlx_is_key_down(engine->mlx, MLX_KEY_SPACE) && ++oriented)
		engine->camera.pos.y += CAM_SPEED * engine->frame.delta;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_LEFT_CONTROL) && ++oriented)
		engine->camera.pos.y -= CAM_SPEED * engine->frame.delta;
	return (oriented);
}

static void	move_left_right(t_camera *cam, int dir)
{
	t_vec3d	norm;
	float	dz;
	float	dx;
	long	delta;

	dz = cam->dir.z;
	dx = cam->dir.x;
	delta = get_engine()->frame.delta;
	norm.y = 0;
	norm.x = -dz;
	norm.z = dx;
	if (dir == LEFT)
		scale_vec3d(&norm, CAM_SPEED * delta);
	else
		scale_vec3d(&norm, -CAM_SPEED * delta);
	add_vec3d(&cam->pos, norm);
}

static void	look_up_down(t_camera *camera, float dy)
{
	t_vec3d	tmp;
	float	dt;

	dt = get_engine()->frame.delta;
	tmp = camera->v;
	scale_vec3d(&tmp, -dy * CAM_SENS * dt);
	add_vec3d(&camera->dir, tmp);
	normlize_vec3d(&camera->dir);
}

void	update_camera(void)
{
	t_engine	*engine;

	engine = get_engine();
	engine->update = true;
	update_viewport(&engine->viewport, engine->window);
	engine->update = false;
	engine->moving = true;
	engine->last_move_time = get_seconds(engine);
	engine->recalculate = true;
}

static bool	orient_camera(t_engine *engine)
{
	float	dt;
	float	dy;
	float	dx;

	if (!mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
		return (false);
	dy = engine->mouse.prev_pos.y - engine->mouse.pos.y;
	dx = engine->mouse.prev_pos.x - engine->mouse.pos.x;
	dt = fminf(get_engine()->frame.delta, 1.0f / 30.0f);
	rotatey_vec3d(&engine->camera.dir, CAM_SENS * -dx * dt);
	look_up_down(&engine->camera, CAM_SENS * dy * dt * 0.001f);
	engine->mouse.prev_pos.x = engine->mouse.pos.x;
	engine->mouse.prev_pos.y = engine->mouse.pos.y;
	return (true);
}

void	handle_cam_movement(t_engine *engine)
{
	if (!move_camera(engine))
		return ;
	wait_for_threads();
	update_camera();
}
