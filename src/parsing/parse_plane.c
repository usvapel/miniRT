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

void	additional_values(t_vector *v, t_object *base, char **split, int index)
{
	while (split[index])
	{
		printf("split: %s\n", split[index]);
		if (ft_strcmp(split[index], "ch") == 0)
			link_texture(base, split + index++);
		else if (ft_strcmp(split[index], "img") == 0)
			link_texture(base, split + index++);
		else
		{
			// reflected value. Should maybe have a string identifier as well..
			// add_elem needs to free the object..
			add_elem(v, safe_split(v, split[index]));
			base->material.reflec = ft_atof(((char ***)v->data)[index - 1][0]);
		}
		index++;
	}
}

void	init_plane(t_engine *engine, char **split)
{
	t_plane	*plane;
	t_vector *v;

	puts("parse plane");
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
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
	additional_values(v, &plane->base, split, 4);
	free_vector(v);
	validate_color(plane->base.color);
	validate_normal(plane->normal);
	add_elem(engine->objects, plane);
}
