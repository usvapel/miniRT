#include "minirt.h"

static void	set_values(t_cylinder *cylinder, t_vector *v)
{
	cylinder->base.type = CYLINDER;
	cylinder->base.pos = parse_vec3d(v, v->data[0]);
	cylinder->axis = parse_vec3d(v, v->data[1]);
	cylinder->axis = normalize_vec3d(cylinder->axis);
	cylinder->base.axis = &cylinder->axis;
	cylinder->r = ft_atof(((char ***)v->data)[2][0]) / 2.0f;
	cylinder->h = ft_atof(((char ***)v->data)[3][0]);
	cylinder->base.color = parse_color(v, v->data[4]);
	cylinder->base.texture.index = -1;
	cylinder->base.texture.type = -1;
	cylinder->base.material.reflect = -1;
	cylinder->base.material.refract = -1;
}

void	init_cylinder(t_vector *objects, char **split)
{
	t_cylinder	*cylinder;
	t_vector	*v;

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
		free_split_vector(v);
		runtime_error("failure during memory allocation!");
	}
	set_values(cylinder, v);
	get_additional_values(v, (void *)&cylinder->base, split, 6);
	free_split_vector(v);
	validate_axis(cylinder->axis);
	validate_color(cylinder->base.color);
	add_elem(objects, cylinder);
}
