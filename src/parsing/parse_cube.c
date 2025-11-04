#include "minirt.h"

void	init_cube(t_vector *objects, char **split)
{
	t_vector	*v;
	t_cube	*cube;

	v = new_vector(1);
	v->owns_data = true;
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[4]));
	cube = ft_calloc(1, sizeof(t_cube));
	if (!cube)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	cube->base.type = CUBE;
	cube->base.pos = parse_vec3d(v, v->data[0]);
	cube->w = ft_atof(split[2]);
	cube->h = ft_atof(split[3]);
	cube->base.color = parse_color(v, v->data[1]);
	cube->base.texture.index = -1;
	cube->base.texture.type = -1;
	cube->axis = new_vec3d(0, 1, 0);
	cube->base.axis = &cube->axis;
	get_additional_values(v, (void *)&cube->base, split, 4); // make sure index is correct
	free_vector(v);
	validate_color(cube->base.color);
	add_elem(objects, cube);
}
