#include "minirt.h"

void	init_sphere(t_vector *objects, char **split)
{
	t_vector	*v;
	t_sphere	*sphere;

	v = new_vector(1);
	v->owns_data = true;
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	sphere->base.type = SPHERE;
	sphere->base.pos = parse_vec3d(v, v->data[0]);
	sphere->r = ft_atof(((char ***)v->data)[1][0]) / 2.0f;
	sphere->base.color = parse_color(v, v->data[2]);
	sphere->base.texture.index = -1;
	sphere->base.texture.type = -1;
	get_additional_values(v, &sphere->base, split, 4);
	free_vector(v);
	validate_color(sphere->base.color);
	add_elem(objects, sphere);
}
