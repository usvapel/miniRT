#include "minirt.h"

static void	scale_object(void *obj);

void	scale_objects(t_engine *engine)
{
	t_ray	ray;
	void	*obj;

	if (mlx_is_mouse_down(engine->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		obj = inside_object(&ray, engine->mouse.pos.x, engine->mouse.pos.y);
		if (!obj)
			return ;
		engine->moving = true;
		scale_object(obj);
	}
}

static void	scale_object(void *obj)
{
	const t_engine	*engine = get_engine();
	const float		dx = engine->mouse.prev_pos.x - engine->mouse.pos.x;
	const float		dy = engine->mouse.prev_pos.y - engine->mouse.pos.y;
	const t_object	*base = get_base_object(obj);

	if (base->type == CUBE)
		scale_cube((t_cube *)obj, dx, dy, engine->frame.delta);
	else if (base->type == SPHERE)
		scale_sphere((t_sphere *)obj, dx, engine->frame.delta);
	else if (base->type == CYLINDER)
		scale_cylinder((t_cylinder *)obj, dx, dy, engine->frame.delta);
	else if (base->type == PARABOLOID)
		scale_paraboloid((t_paraboloid *)obj, dx, dy, engine->frame.delta);
}
