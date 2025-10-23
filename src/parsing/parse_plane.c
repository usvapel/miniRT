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
	t_plane	*plane;
	t_vector *v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	if (split[4])
		add_elem(v, safe_split(v, split[4]));
	plane = ft_calloc(1, sizeof(t_plane));
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
	if (v->count >= 4)
		plane->base.material.reflec = ft_atof(((char ***)v->data)[3][0]);
	free_vector(v);
	if (split[4] && split[5])
		link_texture(&plane->base, split + 5);
	validate_color(plane->base.color);
	validate_normal(plane->normal);
	add_elem(engine->objects, plane);
}
