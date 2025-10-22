#include "minirt.h"

void	init_ambient(char **split)
{
	t_engine	*engine;
	t_ambient	ambient;
	char		**values[2];

	engine = get_engine();
	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	ambient.base.type = AMBIENT;
	ambient.ratio = ft_atof(values[0][0]);
	ambient.base.color = parse_color(values, values[1]);
	free_values(values, 2);
	if (ambient.ratio < 0.0 || ambient.ratio > 1.0)
		runtime_error("Invalid ambient lighting ratio value (0-1)");
	validate_color(ambient.base.color);
	engine->ambient = ambient;
}
