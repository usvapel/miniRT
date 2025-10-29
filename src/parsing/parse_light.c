#include "minirt.h"

static void	validate_light(t_light light)
{
	if (light.brightness < 0.0f || light.brightness > 1.0f)
		runtime_error("Invalid light brightness value (0-1)");
	if (light.r <= 0.0f)
		runtime_error("invalid light radius!");
}

static void	set_values(t_light *light, t_vector *v)
{
	light->base.type = LIGHT;
	light->base.pos = parse_vec3d(v, v->data[0]);
	light->brightness = ft_atof(((char ***)v->data)[1][0]);
	light->base.color = parse_color(v, v->data[2]);
	light->r = LIGHT_RADIUS;
	if (v->count == 4)
		light->r = ft_atof(((char ***)v->data)[3][0]);
	light->base.material.reflec = 0.0f;
	light->base.material.ignore = true;
	light->base.texture.index = -1;
}

void	init_light(t_vector *objects, char **split)
{
	const t_engine	*engine = get_engine();
	t_light			*light;
	t_vector		*v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed!");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	if (split[4])
		add_elem(v, safe_split(v, split[4]));
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	set_values(light, v);
	free_vector(v);
	validate_light(*light);
	validate_color(light->base.color);
	add_elem(objects, light);
	add_elem(engine->lights, light);
}
