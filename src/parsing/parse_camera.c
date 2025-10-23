#include "minirt.h"

static void	validate_camera(t_engine *engine)
{
	static bool is_initialized = false;

	if (engine->camera.fov < 0 || engine->camera.fov > 180)
		runtime_error("Invalid FOV value");
	if (engine->camera.dir.x < -1 || engine->camera.dir.x > 1)
		runtime_error("Invalid orientation x value");
	if (engine->camera.dir.y < -1 || engine->camera.dir.y > 1)
		runtime_error("Invalid orientation y value");
	if (engine->camera.dir.z < -1 || engine->camera.dir.z > 1)
		runtime_error("Invalid orientation z value");
	if (is_initialized)
		runtime_error("Too many cameras!");
	is_initialized = true;
}

void	init_camera(t_engine *engine, char **split)
{
	t_vector *v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	if (split[4])
	{
		free_vector(v);
		runtime_error("too many values to camera!");
	}
	engine->camera.pos = parse_vec3d(v, v->data[0]);
	engine->camera.dir = parse_vec3d(v, v->data[1]);
	engine->camera.fov = ft_atof(((char ***)v->data)[2][0]);
	free_vector(v);
	validate_camera(engine);
}
