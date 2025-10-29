#include "minirt.h"

static void		set_values(t_paraboloid *para, t_vector *v)
{
	para->base.type = PARABOLOID;
	para->base.pos = parse_vec3d(v, v->data[0]);
	para->axis = parse_vec3d(v, v->data[1]);
	para->focal = ft_atof(((char ***)v->data)[2][0]);
	para->h = ft_atof(((char ***)v->data)[3][0]);
	para->base.color = parse_color(v, v->data[4]);
	para->base.texture.index = -1;
	para->base.texture.type = -1;
	para->base.axis = &para->axis;
}

void	init_paraboloid(t_vector *objects, char **split)
{
	t_paraboloid	*para;
	t_vector		*v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	add_elem(v, safe_split(v, split[4]));
	add_elem(v, safe_split(v, split[5]));
	para = ft_calloc(1, sizeof(t_paraboloid));
	if (!para)
	{
		free_vector(v);
		runtime_error("failure during memory allocation!");
	}
	set_values(para, v);
	get_additional_values(v, &para->base, split, 6);
	free_vector(v);
	validate_axis(para->axis);
	para->axis = normalize_vec3d(para->axis);
	validate_color(para->base.color);
	add_elem(objects, para);
}
