#include "minirt.h"

void	init_paraboloid(t_vector *objects, char **split)
{
	char			**values[6];
	t_paraboloid	*para;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	if (split[6])
		values[5] = safe_split(values, 5, split[6]);
	para = ft_calloc(1, sizeof(t_paraboloid));
	if (!para)
	{
		free_values(values, 6);
		runtime_error("failure during memory allocation!");
	}
	para->base.type = PARABOLOID;
	para->base.pos = parse_vec3d(values, values[0]);
	para->axis = parse_vec3d(values, values[1]);
	para->focal = ft_atof(values[2][0]);
	para->h = ft_atof(values[3][0]);
	para->base.color = parse_color(values, values[4]);
	para->axis = normalize_vec3d(para->axis);
	para->base.material.reflec = ft_atof(values[5][0]);
	free_values(values, 6);
	validate_axis(para->axis);
	validate_color(para->base.color);
	add_elem(objects, para);
}
