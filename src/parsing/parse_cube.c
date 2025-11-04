#include "minirt.h"
#include "parsing.h"

static void	add_values(t_vector *v, t_cube *cube)
{
	cube->base.type = CUBE;
	cube->base.pos = parse_vec3d(v, v->data[0]);
	cube->w = ft_atof(((char ***)v->data)[1][0]);
	cube->h = ft_atof(((char ***)v->data)[2][0]);
	cube->base.color = parse_color(v, v->data[4]);
	cube->base.texture.index = -1;
	cube->base.texture.type = -1;
	cube->axis = parse_vec3d(v, v->data[3]);
	cube->base.axis = &cube->axis;
}

void	init_cube(t_vector *objects, char **split)
{
	t_vector	*v;
	t_cube		*cube;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	add_elem(v, safe_split(v, split[4]));
	add_elem(v, safe_split(v, split[5]));
	cube = ft_calloc(1, sizeof(t_cube));
	if (!cube)
	{
		free_split_vector(v);
		runtime_error("failure during memory allocation!");
	}
	add_values(v, cube);
	get_additional_values(v, (void *)&cube->base, split, 6);
	free_split_vector(v);
	validate_color(cube->base.color);
	add_elem(objects, cube);
}
