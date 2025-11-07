#include "minirt.h"

void	init_checkerboard_text(t_vector *checkers, char **split)
{
	t_checker	*check;
	t_vector	*v;

	check = ft_calloc(1, sizeof(t_checker));
	if (!check)
		runtime_error("allocation failed");
	v = new_vector(1);
	if (!v)
	{
		free(check);
		runtime_error("allocation failed");
	}
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	check->color1 = parse_color(v, v->data[0]);
	check->color2 = parse_color(v, v->data[1]);
	check->block_size = 3.0;
	get_additional_texture_values(check, CHECKERBOARD, split, 3);
	free_split_vector(v);
	print_vec(color_to_vec3d(check->color1), "Color: ");
	add_elem(checkers, check);
}

void	init_image_text(t_vector *images, char **split)
{
	t_image_text	*text;

	text = ft_calloc(1, sizeof(t_image_text));
	if (!text)
		runtime_error("allocation failed");
	printf("Initializing image texture: %s\n", split[2]);
	text->texture = mlx_load_png(split[2]);
	text->txt_source = ft_strdup(split[2]);
	text->block_size = 1.0;
	if (!text->texture)
	{
		free(text);
		runtime_error(ft_strjoin("failed to load ", split[2]));
	}
	text->bump = NULL;
	if (split[3])
	{
		printf("Initializing bump image texture: %s\n", split[3]);
		text->bump = mlx_load_png(split[3]);
		text->bump_source = ft_strdup(split[3]);
	}
	get_additional_texture_values(text, IMAGE, split, 3);
	add_elem(images, text);
}

void	link_texture(t_object *obj, char **split, int type)
{
	obj->texture.type = type;
	obj->texture.index = ft_atoi(split[1]);
	printf("Linkage type: %d, i: %d\n", obj->type, obj->texture.index);
}
