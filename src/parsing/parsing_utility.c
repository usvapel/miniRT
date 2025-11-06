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

void	runtime_error(char *s)
{
	t_engine	*engine;

	engine = get_engine();
	printf("Error\n");
	printf("%s\n", s);
	free_vector(engine->objects);
	free_vector(engine->g_lights);
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
