#include "minirt.h"

static void    move_pos_left_right(t_camera *cam, t_vec3d *pos, float d);
static void	move_object(void *obj, t_ray ray, float dx, float dy);
static void    move_pos_left_right(t_camera *cam, t_vec3d *pos, float d);

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

void *inside_object(t_ray *ray, double x, double y, int *type)
{
	t_engine *engine = get_engine();
	*ray = get_ray(x, y);
	t_hit hit = {0};

	object_intersection(engine, ray, &hit);
	if (!hit.prev_hit)
		return (NULL);
	*type = hit.type;
	return (hit.obj);
}

static void move_object(void *obj, t_ray ray, float dx, float dy)
{
	t_object *base = (t_object*)obj;
	t_vec3d tmp = base->pos;
	t_vec3d b = {0,1.0,0};
	long dt = get_engine()->frame.delta;
	
	minus_vec3d(&tmp, ray.origin);
	dy *= magnitude_vec3d(tmp) * OBJ_SPEED * dt;
	dx *= magnitude_vec3d(tmp) * OBJ_SPEED * dt;
	move_pos_left_right(&get_engine()->camera, &base->pos, dx);
	scale_vec3d(&b, dy);
	add_vec3d(&base->pos, b);
	update_camera();
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

static void    move_pos_left_right(t_camera *cam, t_vec3d *pos, float d)
{
    t_vec3d norm;
    float dz = cam->dir.z;
    float dx = cam->dir.x;
    norm.y = 0;
    norm.x = -dz;
    norm.z = dx;
    scale_vec3d(&norm, d);
    add_vec3d(pos, norm);
}