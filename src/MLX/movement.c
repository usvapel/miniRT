#include "minirt.h"

void movement(t_engine *engine)
{
	if (!move_camera(engine))
		return ;
	wait_for_threads();
	update_camera();
}

void scale_objects(t_engine *engine)
{
	t_ray ray;
	int type;
	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		void *obj = inside_object(&ray, engine->mouse.pos.x, engine->mouse.pos.y, &type);
		if (!obj)
			return ;
		scale_object(obj, engine->mouse.pos.x, engine->mouse.pos.y);
		update_camera();
	}
}

// void rotate_objects(t_engine *engine)
// {
// 	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
// 	{
// 		t_sphere *sphere = inside_object(engine->mouse.pos.x, engine->mouse.pos.y);
// 		if (!sphere)
// 			return ;
// 		rotate_object(engine->mouse.pos.x, engine->mouse.pos.y);
// 		update_camera();
// 	}
// }
t_vec3d *get_obj_pos(void *obj)
{
	if (*(int *)obj == SPHERE)
		return &((t_sphere *)obj)->pos;
	if (*(int *)obj == PLANE)
		return &((t_plane *)obj)->pos;
	if (*(int *)obj == CYLINDER)
		return &((t_cylinder *)obj)->pos;
	if (*(int *)obj == LIGHT) 
		return &((t_light *)obj)->pos;
	return &((t_paraboloid *)obj)->pos;
}
void move_object(void *obj, t_ray ray, float dx, float dy)
{
	t_vec3d *pos = get_obj_pos(obj);
	t_vec3d tmp = *pos;
	t_vec3d b = {0,0.001,0};
	
	minus_vec3d(&tmp, ray.origin);
	dy *= magnitude_vec3d(tmp) * 0.4;
	dx *= magnitude_vec3d(tmp) * 0.4;
	move_pos_left_right(&get_engine()->camera, pos, dx);
	scale_vec3d(&b, dy);
	add_vec3d(pos, b);
	update_camera();
}

void move_objects(t_engine *engine)
{
	static t_ray ray;
	static void *obj = NULL;
	static bool grabbed = false;
	float dy;
	float dx;
	int type;

	dy = engine->mouse.prev_pos.y - engine->mouse.pos.y;
	dx = engine->mouse.prev_pos.x - engine->mouse.pos.x;

	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (grabbed == false)
		{
			obj = inside_object(&ray, engine->mouse.pos.x, engine->mouse.pos.y, &type);
			if (!obj)
				return ;
			grabbed = true;
		}
		move_object(obj, ray, dx, dy);
	}
	else
		grabbed = false;
}

void	key_hook(void *param)
{
	t_engine	*engine;
	int x; int y;

	engine = (t_engine *)param;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit();

	mlx_get_mouse_pos(engine->mlx, &x, &y);
	engine->mouse.prev_pos = engine->mouse.pos;
	engine->mouse.pos.x = x;
	engine->mouse.pos.y = y;
	if (mlx_is_key_down(engine->mlx, MLX_KEY_C))
		scale_objects(engine);
	// else if (mlx_is_key_down(engine->mlx, MLX_KEY_X))
	// 	rotate_objects();
	else if (mlx_is_key_down(engine->mlx, MLX_KEY_Z))
		move_objects(engine);
	else
		movement(engine);
}
