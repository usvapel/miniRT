#include "minirt.h"

void	init_plane(t_engine *engine, char **split)
{
	char	**values[3];
	t_plane	*plane;

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	plane->base.type = PLANE;
	plane->base.pos = parse_vec3d(values, values[0]);
	plane->normal = parse_vec3d(values, values[1]);
	plane->base.color = parse_color(values, values[2]);
	free_values(values, 3);
	validate_color(plane->base.color);
	if (plane->normal.x < -1.0f || plane->normal.x > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	if (plane->normal.y < -1.0f || plane->normal.y > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	if (plane->normal.z < -1.0f || plane->normal.z > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	add_elem(engine->objects, plane);
}
