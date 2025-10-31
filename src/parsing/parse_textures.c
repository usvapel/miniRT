#include "minirt.h"

void	init_checkerboard_text(t_vector *checkers, char **split)
{
	t_checker *check = ft_calloc(1, sizeof(t_checker));
	t_vector *v;

	puts("parse checkerboard");
	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[2]));
	add_elem(v, safe_split(v, split[3]));
	check->color1 = parse_color(v, v->data[0]);
	check->color2 = parse_color(v, v->data[1]);
	check->block_size = ft_atof(split[4]);
	free_vector(v);
	printf("block size: %f\n", check->block_size);
	print_vec(color_to_vec3d(check->color1), "Color: ");
	add_elem(checkers, check);
	// exit(1);
}

void	init_image_text(t_vector *images, char **split)
{
	t_image_text *text = ft_calloc(1, sizeof(t_image_text));
	printf("Initializing image texture: %s\n", split[2]);
	text->texture = mlx_load_png(split[2]);
	text->bump = NULL;
	text->texture = mlx_load_png(split[2]);
	if (split[3])
		text->bump = mlx_load_png(split[3]);
	add_elem(images, text);
}

void	link_texture(t_object *obj, char **split, int type)
{
	obj->texture.type = type;
	obj->texture.index = ft_atoi(split[1]);
	printf("Linkage type: %d, i: %d\n",obj->type, obj->texture.index);
}

