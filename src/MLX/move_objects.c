#include "minirt.h"

static void move_object(void *obj, double mouse_x, double mouse_y)
{
	t_object *base = get_base_object(obj);
	t_ray new_ray = get_ray(mouse_x, mouse_y);
	float distance = magnitude_vec3d(sub_vec3d(base->pos, new_ray.origin));
	t_vec3d new_pos = add2_vec3d(new_ray.origin, nscale_vec3d(new_ray.udir, distance));
	base->pos = new_pos;
	update_camera();
}

void *inside_object(t_ray *ray, double x, double y, int *type)
{
	t_engine *engine = get_engine();
	*ray = get_ray(x, y);
	t_hit hit = {0};

	objects_intersection(engine, ray, &hit);
	if (!hit.prev_hit)
		return (NULL);
	*type = hit.type;
	return (hit.obj);
}

void move_objects(t_engine *engine)
{
	static t_ray ray;
	static void *obj = NULL;
	static bool grabbed = false;
	int type;

	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (grabbed == false)
		{
			obj = inside_object(&ray, engine->mouse.pos.x, engine->mouse.pos.y, &type);
			if (!obj)
				return ;
			grabbed = true;
		}
		move_object(obj, engine->mouse.pos.x, engine->mouse.pos.y);
	}
	else
		grabbed = false;
}

void rotate_object(void *obj, float dx, float dy)
{
	t_object *base = get_base_object(obj);
	t_vec3d tmp = base->pos;
	long dt = get_engine()->frame.delta;
	t_camera camera = get_engine()->camera;
	if (!base->axis)
		return;
	t_basis3d local = build_local_basis(camera.u);
	t_vec3d axis = vec_in_basis(*base->axis, local);
	minus_vec3d(&tmp, ray.origin);
	dy *= magnitude_vec3d(tmp) * OBJ_SPEED * dt;
	dx *= magnitude_vec3d(tmp) * OBJ_SPEED * dt;
	rotateY_vec3d(&axis, -dy * 100);
	rotateZ_vec3d(&axis, dx * 100);
	*base->axis = point_from_basis(axis, local, new_vec3d(0,0,0));
	normlize_vec3d(base->axis);
	update_camera();
}

void rotate_objects(t_engine *engine)
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
		rotate_object(obj, ray, dx, dy);
	}
	else
		grabbed = false;
}
