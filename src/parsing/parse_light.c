#include "minirt.h"

static void	validate_light(t_generic_light g_light)
{
	if (g_light.brightness < 0.0f || g_light.brightness > 1.0f)
		runtime_error("Invalid light brightness value (0-1)");
}

static void	set_values(t_generic_light *g_light, t_point_light *light, t_vector *v, char **split)
{
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	g_light->base.type = POINT_LIGHT;
	light->axis = new_vec3d(0,1,0);
	g_light->base.pos = parse_vec3d(v, v->data[0]);
	g_light->brightness = ft_atof(((char ***)v->data)[1][0]);
	g_light->base.color = parse_color(v, v->data[2]);
	g_light->obj_index = -1;
	g_light->base.axis = &light->axis;
	g_light->base.material.reflec = 0.0f;
	g_light->base.material.ignore = true;
	g_light->base.texture.index = -1;
	get_additional_values(v, (void *)g_light, split, 4);
}
static void	set_values2(t_generic_light *g_light, t_spot_light *light, t_vector *v, char **split)
{
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	add_elem(v, safe_split(v, split[4]));
	add_elem(v, safe_split(v, split[5]));
	add_elem(v, safe_split(v, split[6]));
	g_light->base.type = SPOT_LIGHT;
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
	get_additional_values(v, (void *)g_light, split, 7);
}

void	init_light(t_vector *lights, char **split)
{
	t_generic_light *g_light;
	t_point_light	*light;
	t_vector *v;

	puts("parse point light");
	g_light = ft_calloc(1,sizeof(t_generic_light));
	if (!g_light)
		runtime_error("failure during memory allocation!");
	add_elem(lights, g_light);
	light = ft_calloc(1, sizeof(t_point_light));
	if (!light)
		runtime_error("failure during memory allocation!");
	g_light->light = (void *)light;
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	validate_color(g_light->base.color);
	set_values(g_light, light, v, split);
	free_vector(v);
	validate_light(*g_light);
	validate_color(g_light->base.color);
}
void	init_spot_light(t_vector *lights, char **split)
{
	t_generic_light *g_light;
	t_spot_light	*light;
	t_vector *v;

	puts("parse spot light");
	g_light = ft_calloc(1,sizeof(t_generic_light));
	if (!g_light)
		runtime_error("failure during memory allocation!");
	add_elem(lights, g_light);
	light = ft_calloc(1, sizeof(t_spot_light));
	if (!light)
		runtime_error("failure during memory allocation!");
	g_light->light = light;
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	set_values2(g_light, light, v, split);
	free_vector(v);
	validate_color(g_light->base.color);
	validate_light(*g_light);
	add_elem(lights, g_light);
}
