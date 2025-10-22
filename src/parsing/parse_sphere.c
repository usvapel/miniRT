#include "minirt.h"

void	init_sphere(t_vector *objects, char **split)
{
	char		**values[3];
	t_sphere	*sphere;

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	sphere->base.type = SPHERE;
	sphere->base.pos = parse_vec3d(values, values[0]);
	sphere->r = ft_atof(values[1][0]) / 2.0f;
	sphere->base.color = parse_color(values, values[2]);
	sphere->base.texture.index = -1;
	sphere->base.texture.type = -1;
	if (split[4])
		link_texture(&sphere->base, split + 4);
	free_values(values, 3);
	validate_color(sphere->base.color);
	add_elem(objects, sphere);
}
