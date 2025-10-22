#include "minirt.h"

void	init_sphere(t_vector *objects, char **split)
{
	char		**values[4];
	t_sphere	*sphere;

	printf("init_sphere\n");
	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	if (split[4])
		values[3] = safe_split(values, 3, split[4]);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
	{
		free_values(values, 4);
		runtime_error("failure during memory allocation!");
	}
	sphere->base.type = SPHERE;
	sphere->base.pos = parse_vec3d(values, values[0]);
	sphere->r = ft_atof(values[1][0]) / 2.0f;
	sphere->base.color = parse_color(values, values[2]);
	if (values[3])
		sphere->base.material.reflec = ft_atof(values[3][0]);
	free_values(values, 4);
	validate_color(sphere->base.color);
	add_elem(objects, sphere);
}
