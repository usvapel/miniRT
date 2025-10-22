#include "minirt.h"

void	init_cylinder(t_vector *objects, char **split)
{
	char		**values[5];
	t_cylinder	*cylinder;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		free_values(values, 5);
		runtime_error("failure during memory allocation!");
	}
	cylinder->base.type = CYLINDER;
	cylinder->base.pos = parse_vec3d(values, values[0]);
	cylinder->axis = parse_vec3d(values, values[1]);
	cylinder->r = ft_atof(values[2][0]) / 2;
	cylinder->h = ft_atof(values[3][0]);
	cylinder->base.color = parse_color(values, values[4]);
	cylinder->axis = normalize_vec3d(cylinder->axis);
	cylinder->material.reflectiveness = 0.0f;
	free_values(values, 5);
	validate_axis(cylinder->axis);
	validate_color(cylinder->base.color);
	add_elem(objects, cylinder);
}
