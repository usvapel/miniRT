#include "minirt.h"

void	init_ambient(char **split)
{
	t_engine	*engine;
	t_ambient	ambient;
	t_vector	*v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed!");
	engine = get_engine();
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	ambient.base.type = AMBIENT;
	ambient.ratio = ft_atof(((char ***)v->data)[0][0]);
	ambient.base.color = parse_color(v, v->data[1]);
	free_split_vector(v);
	if (ambient.ratio < 0.0 || ambient.ratio > 1.0)
		runtime_error("Invalid ambient lighting ratio value (0-1)");
	validate_color(ambient.base.color);
	engine->ambient = ambient;
}
