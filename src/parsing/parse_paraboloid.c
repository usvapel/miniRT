#include "minirt.h"

void	init_paraboloid(t_vector *objects, char **split)
{
	char			**values[5];
	t_paraboloid	*para;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	para = malloc(sizeof(t_paraboloid));
	if (!para)
	{
		free_values(values, 5);
		runtime_error("failure during memory allocation!");
	}
	para->base.type = PARABOLOID;
	para->base.pos = parse_vec3d(values, values[0]);
	para->axis = parse_vec3d(values, values[1]);
	para->focal = ft_atof(values[2][0]);
	para->h = ft_atof(values[3][0]);
	para->base.color = parse_color(values, values[4]);
	para->axis = normalize_vec3d(para->axis);
	free_values(values, 5);
	validate_axis(para->axis);
	validate_color(para->base.color);
	add_elem(objects, para);
}
