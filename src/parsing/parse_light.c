#include "minirt.h"

static void	validate_light(t_light light)
{
	if (light.brightness < 0.0f || light.brightness > 1.0f)
		runtime_error("Invalid light brightness value (0-1)");
}

static void	set_values(t_generic_light *g_light, t_point_light light, t_vector *v, char **split)
{
	g_light->base.axis = new_vec3d(0,1,0);
	g_light->base.pos = parse_vec3d(v, v->data[0]);
	g_light->brightness = ft_atof(((char ***)v->data)[1][0]);
	g_light->base.color = parse_color(v, v->data[2]);
	g_light->obj_index = -1;
	g_light->base.axis = &light->axis;
	g_light->base.material.reflec = 0.0f;
	g_light->base.material.ignore = true;
	g_light->base.texture.index = -1;
	get_additional_values(v, &g_light->base, split, 4);
	(void )v;
}

static t_generic_light	*init_glight(t_vector *lights, int type)
{
	t_generic_light *g_light;
	
	g_light = ft_calloc(1,sizeof(t_generic_light));
	if (!g_light)
		runtime_error("failure during memory allocation!");
	g_light->base.type = type;
	add_elem(lights, g_light);
	return (g_light);
}

void	init_light(t_vector *lights, char **split)
{
	t_generic_light *g_light;
	t_point_light	*light;
	t_vector *v;

	puts("parse point light");
	g_light = init_glight(lights, POINT_LIGHT);
	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		runtime_error("failure during memory allocation!");
	g_light->light = (void *)light;
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	validate_color(g_light->base.color);
	set_values(g_light, light, v, split);
	free_vector(v);
	validate_light(*light);
	validate_color(light->base.color);
}
void	init_spot_light(t_vector *lights, char **split)
{
	t_generic_light *g_light;
	t_spot_light	*light;
	t_vector *v;

	puts("parse spot light");
	g_light = init_glight(lights, SPOT_LIGHT);
	light = ft_calloc(1, sizeof(t_spot_light));
	if (!light)
		runtime_error("failure during memory allocation!");
	g_light->light = light;
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	add_elem(v, safe_split(v, split[4]));
	add_elem(v, safe_split(v, split[5]));
	add_elem(v, safe_split(v, split[6]));
	g_light->base.pos = parse_vec3d(v, v->data[0]);
	light->axis = parse_vec3d(v, v->data[1]);
	g_light->base.axis = &light->axis;
	g_light->brightness = ft_atof(((char ***)v->data)[2][0]);
	light->range = ft_atof(((char ***)v->data)[3][0]);
	light->fov = ft_atof(((char ***)v->data)[4][0]);
	g_light->base.color = parse_color(v, v->data[5]);
	g_light->base.material.reflec = 0.0f;
	g_light->base.material.ignore = true;
	g_light->base.texture.index = -1;
	g_light->obj_index = -1;
	get_additional_values(v, &g_light->base, split, 7);
	free_vector(v);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		runtime_error("Invalid light brightness value (0-1)");
	validate_color(g_light->base.color);
	add_elem(lights, g_light);
}
