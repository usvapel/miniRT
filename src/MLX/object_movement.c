
#include "minirt.h"

bool inside_object(double x, double y)
{
	t_engine *engine = get_engine();
	t_sphere *sphere = engine->objects[0];
	t_ray ray = get_ray(x, y);
	t_hit hit;

	hit.prev_hit = false;
	sphere_hit(*sphere, ray, &hit);
	if (hit.prev_hit)
		return (true);
	else
		return (false);
}

void update_pos(float d)
{
	t_engine *engine = get_engine();
	t_sphere *sphere = engine->objects[0];
	sphere->r += 0.01 * d;
}

void    move_object(t_engine *engine)
{
	static double previous_length;
	static t_vec3d previous_mouse;
	double current_length;
	t_vec3d current_mouse;
	current_mouse = new_vec3d(engine->mouse_x, engine->mouse_y, 0);
	previous_length = pow_magnitude_vec3d(previous_mouse);
	current_length = pow_magnitude_vec3d(current_mouse);
	if (previous_length < current_length)
		update_pos(1);
	if (previous_length > current_length)
		update_pos(-1);
	// if (inside_object(engine->mouse_x, engine->mouse_y))
	// 	update_pos();
	previous_mouse = new_vec3d(engine->mouse_x, engine->mouse_y, 0);
	previous_length = current_length;
}
