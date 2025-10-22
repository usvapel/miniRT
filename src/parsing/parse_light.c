#include "minirt.h"

void	init_light(t_vector *objects, char **split)
{
	const t_engine	*engine = get_engine();
	char			**values[3];
	t_light			*light;

	printf("init_light\n");
	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	light->base.type = LIGHT;
	light->base.pos = parse_vec3d(values, values[0]);
	light->brightness = ft_atof(values[1][0]);
	light->base.color = parse_color(values, values[2]);
	light->r = LIGHT_RADIUS;
	light->base.material.reflec = 0.0f;
	light->base.material.ignore = true;
	free_values(values, 3);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		runtime_error("Invalid light brightness value (0-1)");
	validate_color(light->base.color);
	add_elem(objects, light);
	add_elem(engine->lights, light);
}
