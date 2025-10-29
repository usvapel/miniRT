#include "minirt.h"

void	init_cylinder(t_vector *objects, char **split)
{
	t_cylinder	*cylinder;
	t_vector *v;

	puts("parse cylinder");
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	add_elem(v, safe_split(v, split[4]));
	add_elem(v, safe_split(v, split[5]));
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	cylinder->base.type = CYLINDER;
	cylinder->base.pos = parse_vec3d(v, v->data[0]);
	cylinder->axis = parse_vec3d(v, v->data[1]);
	cylinder->r = ft_atof(((char ***)v->data)[2][0]) / 2.0f;
	cylinder->h = ft_atof(((char ***)v->data)[3][0]);
	cylinder->base.color = parse_color(v, v->data[4]);
	cylinder->axis = normalize_vec3d(cylinder->axis);
	cylinder->base.texture.index = -1;
	cylinder->base.texture.type = -1;
	cylinder->base.axis = &cylinder->axis;
	get_additional_values(v, &cylinder->base, split, 6); // make sure index is correct
	free_vector(v);
	validate_axis(cylinder->axis);
	validate_color(cylinder->base.color);
	add_elem(objects, cylinder);
}
