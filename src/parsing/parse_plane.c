#include "minirt.h"

static void	validate_normal(t_vec3d normal)
{
	if (normal.x < -1.0f || normal.x > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
	if (normal.y < -1.0f || normal.y > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
	if (normal.z < -1.0f || normal.z > 1.0f)
		runtime_error("Invalid normal (-1 - 1)");
}

void	init_plane(t_engine *engine, char **split)
{
	t_plane		*plane;
	t_vector	*v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	plane = ft_calloc(1, sizeof(t_plane));
	add_elem(engine->objects, plane);
	if (!plane)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	plane->base.type = PLANE;
	plane->base.pos = parse_vec3d(v, v->data[0]);
	plane->normal = parse_vec3d(v, v->data[1]);
	plane->base.color = parse_color(v, v->data[2]);
	plane->base.texture.index = -1;
	plane->base.axis = &plane->normal;
	get_additional_values(v, &plane->base, split, 4); // make sure index is correct
	free_vector(v);
	validate_color(plane->base.color);
	validate_normal(plane->normal);
}
