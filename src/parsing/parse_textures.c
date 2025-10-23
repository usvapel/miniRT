#include "minirt.h"

void	init_checkerboard_text(t_vector *checkers, char **split)
{
	char	**values[2];
	t_checker *check = malloc(sizeof(t_checker));
	t_vector *v;

	v = new_vector(1);
	if (!v)
		runtime_error("allocation failed");
	add_elem(v, safe_split(v, split[1]));
	add_elem(v, safe_split(v, split[2]));
	check->color1 = parse_color(v, v->data[0]);
	check->color2 = parse_color(v, v->data[1]);
	check->block_size = ft_atof(split[4]);
	printf("block size: %f\n", check->block_size);
	print_vec(color_to_vec3d(check->color1), "Color: ");
	add_elem(checkers, check);
	free_values(values, 2);
	// exit(1);
}

void	init_image_text(t_vector *images, char **split)
{
	t_image_text *text = malloc(sizeof(t_image_text));
	printf("Initializing image texture: %s\n", split[2]);
	text->texture = mlx_load_png(split[2]);
	add_elem(images, text);
}

void	link_texture(t_object *obj, char **split)
{

	if (!split || !*split || !*(split + 1))
	{
		printf("Invalid linkage to texture\n");
		// exit(1);
	}
	if (ft_strcmp(split[0], "ch") == 0)
	{
		obj->texture.type = CHECKERBOARD;
		obj->texture.index = ft_atoi(split[1]);
	}
	else if (ft_strcmp(split[0], "img") == 0)
	{
		obj->texture.type = IMAGE;
		obj->texture.index = ft_atoi(split[1]);
	}
	else
		printf("Invalid texture type: %s\n", split[1]);
	
	printf("Linkage type: %d, i: %d\n",obj->type, obj->texture.index);
}
