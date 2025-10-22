#include "minirt.h"

void	init_cylinder(t_vector *objects, char **split)
{
	char		**values[6];
	t_cylinder	*cylinder;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	if (split[6])
		values[5] = safe_split(values, 5, split[6]);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
	{
		free_values(values, 6);
		runtime_error("failure during memory allocation!");
	}
	cylinder->base.type = CYLINDER;
	cylinder->base.pos = parse_vec3d(values, values[0]);
	cylinder->axis = parse_vec3d(values, values[1]);
	cylinder->r = ft_atof(values[2][0]) / 2;
	cylinder->h = ft_atof(values[3][0]);
	cylinder->base.color = parse_color(values, values[4]);
	cylinder->axis = normalize_vec3d(cylinder->axis);
	if (values[5])
		cylinder->base.material.reflec = ft_atof(values[5][0]);
	free_values(values, 6);
	validate_axis(cylinder->axis);
	validate_color(cylinder->base.color);
	add_elem(objects, cylinder);
}
