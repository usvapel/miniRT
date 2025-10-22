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
	char	**values[3];

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	if (split[4])
	{
		free_values(values, 3);
		runtime_error("too many values in camera!");
	}
	engine->camera.pos = parse_vec3d(values, values[0]);
	engine->camera.dir = parse_vec3d(values, values[1]);
	engine->camera.fov = ft_atof(values[2][0]);
	free_values(values, 3);
	validate_camera(engine);
}
