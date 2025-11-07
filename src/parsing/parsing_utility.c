#include "minirt.h"

void	get_additional_values(t_vector *v, void *obj, char **split, int index)
{
	t_object	*base;

	base = obj;
	while (split[index])
	{
		if (ft_strcmp(split[index], "ch") == 0 && split[index + 1])
			link_texture(base, split + index, CHECKERBOARD);
		else if (ft_strcmp(split[index], "img") == 0 && split[index + 1])
			link_texture(base, split + index, IMAGE);
		else if (ft_strcmp(split[index], "obj") == 0 && split[index + 1])
			((t_generic_light *)obj)->obj_index = ft_atof(split[index + 1]);
		else if (ft_strcmp(split[index], "rl") == 0 && split[index + 1])
		{
			base->material.reflect = ft_atof(split[index + 1]);
			if (base->material.reflect > 1.0f || base->material.reflect < 0.0f)
			{
				free_split_vector(v);
				runtime_error("invalid reflection value! (0 - 1)");
			}
		}
		else if (ft_strcmp(split[index], "rf") == 0 && split[index + 1])
			base->material.refract = ft_atof(split[index + 1]);
		index++;
	}
}

void	get_additional_texture_values(void *txt, t_texture_type type,
		char **split, int index)
{
	float	*block_size;

	if (type == CHECKERBOARD)
		block_size = &(((t_checker *)txt)->block_size);
	else if (type == IMAGE)
		block_size = &((t_image_text *)txt)->block_size;
	while (split[index])
	{
		if (ft_strcmp(split[index], "s") == 0 && split[index + 1])
		{
			*block_size = ft_atof(split[index + 1]);
			if (*block_size <= 0)
				runtime_error("invalid texture size value! ( size > 0)");
		}
		index++;
	}
}

void	runtime_error(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
	cleanup_data();
	exit(EXIT_FAILURE);
}

void	free_array(void **array)
{
	void	**copy;

	if (!array)
		return ;
	copy = array;
	while (*copy)
		free(*copy++);
	free(array);
}

void	free_values(char **values[], int count)
{
	int	i;

	i = 0;
	while (i < count && values[i])
	{
		if (!values[i][0])
			break ;
		free_array((void *)values[i]);
		i++;
	}
}
