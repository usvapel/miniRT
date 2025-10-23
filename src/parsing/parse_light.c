#include "minirt.h"
#include "vector.h"

void	init_light(t_vector *objects, char **split)
{
	const t_engine	*engine = get_engine();
	t_light			*light;
	t_vector *v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	light = malloc(sizeof(t_light));
	if (!light)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	light->base.type = LIGHT;
	light->base.pos = parse_vec3d(v, v->data[0]);
	light->brightness = ft_atof(v->data[1]);
	light->base.color = parse_color(v, v->data[2]);
	light->r = LIGHT_RADIUS;
	light->base.material.reflec = 0.0f;
	light->base.material.ignore = true;
	light->base.texture.index = -1;
	free_vector(v);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		runtime_error("Invalid light brightness value (0-1)");
	validate_color(light->base.color);
	add_elem(objects, light);
	add_elem(engine->lights, light);
}
