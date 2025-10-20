#include "minirt.h"
static void scale_by_factor(void *object, float dx, float dy);
static void    scale_object(void *obj, double x, double y);

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

static void scale_by_factor(void *object, float dx, float dy)
{
	int type = *(int *)object;
	const long dt = get_engine()->frame.delta;

	if (type == SPHERE)
	{
		(*(t_sphere *)object).r += OBJ_S_SPEED * -dx * dt;
		if ((*(t_sphere *)object).r <= 0.05f)
			(*(t_sphere *)object).r = 0.05f;
	}
	if (type == CYLINDER)
	{
		(*(t_cylinder *)object).r += OBJ_S_SPEED * -dx * dt;
		(*(t_cylinder *)object).h += OBJ_S_SPEED * dy * dt;
		if ((*(t_cylinder *)object).r <= 0.05f)
			(*(t_cylinder *)object).r = 0.05f;
		if ((*(t_cylinder *)object).h <= 0.05f)
			(*(t_cylinder *)object).h = 0.05f;
	}
	if (type == LIGHT)
	{
		(*(t_light *)object).r += OBJ_S_SPEED * -dx * dt;
		if ((*(t_light *)object).r <= 0.05f)
			(*(t_light *)object).r = 0.05f;
	}
	if (type == PARABOLOID)
	{
		(*(t_paraboloid *)object).focal += OBJ_S_SPEED * -dx * dt;
		(*(t_paraboloid *)object).h += OBJ_S_SPEED * dy * dt;
		if ((*(t_paraboloid *)object).focal <= 0.05f)
			(*(t_paraboloid *)object).focal = 0.05f;
		if ((*(t_paraboloid *)object).h <= 0.05f)
			(*(t_paraboloid *)object).h = 0.05f;
	}
}

static void    scale_object(void *obj, double x, double y)
{
	t_mouse mouse = get_engine()->mouse;
	(void)x;
	(void)y;
	float 			dx = mouse.prev_pos.x - mouse.pos.x;
	float 			dy = mouse.prev_pos.y - mouse.pos.y;
	scale_by_factor(obj, dx, dy);
}