#include "minirt.h"

static void	validate_normal(t_vec3d normal)
{
	if (normal.x < -1.0f || normal.x > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
	if (normal.y < -1.0f || normal.y > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
	if (normal.z < -1.0f || normal.z > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
}

void	init_plane(t_engine *engine, char **split)
{
	char	**values[4];
	t_plane	*plane;

	printf("init_plane\n");
	ft_memset(values, 0, sizeof(values));
	values[0] = safe_split(values, 4, split[1]);
	values[1] = safe_split(values, 4, split[2]);
	values[2] = safe_split(values, 4, split[3]);
	if (split[4])
		values[3] = safe_split(values, 4, split[4]);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
	{
		free_values(values, 4);
		runtime_error("failure during memory allocation!");
	}
	plane->base.type = PLANE;
	plane->base.pos = parse_vec3d(values, values[0]);
	plane->normal = parse_vec3d(values, values[1]);
	plane->base.color = parse_color(values, values[2]);
	if (values[3])
		plane->base.material.reflec = ft_atof(values[3][0]);
	free_values(values, 4);
	validate_color(plane->base.color);
	validate_normal(plane->normal);
	add_elem(engine->objects, plane);
}
