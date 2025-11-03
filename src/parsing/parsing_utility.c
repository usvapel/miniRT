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
		{
			base->material.refract = ft_atof(split[index + 1]);
			base->material.should_refract = true;
		}
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

char	**safe_split(t_vector *v, char *line)
{
	char	**splitted;

	if (!line)
		runtime_error("invalid/missing values!");
	splitted = ft_split(line, ',');
	if (!splitted)
	{
		free_split_vector(v);
		runtime_error("failure during memory allocation!");
	}
	return (splitted);
}

t_vec3d	parse_vec3d(t_vector *v, char **components)
{
	t_vec3d	vec;

	if (!components[0] || !components[1] || !components[2])
	{
		free_split_vector(v);
		runtime_error("invalid/missing values!");
	}
	vec.x = ft_atof(components[0]);
	vec.y = ft_atof(components[1]);
	vec.z = ft_atof(components[2]);
	return (vec);
}

t_color	parse_color(t_vector *v, char **components)
{
	t_color	color;

	if (!components[0] || !components[1] || !components[2])
	{
		free_split_vector(v);
		runtime_error("invalid/missing values!");
	}
	color.r = ft_atof(components[0]);
	color.g = ft_atof(components[1]);
	color.b = ft_atof(components[2]);
	color.a = 255;
	return (color);
}

void	validate_axis(t_vec3d axis)
{
	if (axis.x < -1.0f || axis.x > 1.0f)
		runtime_error("Invalid obj axis (-1 - 1)");
	if (axis.y < -1.0f || axis.y > 1.0f)
		runtime_error("Invalid obj axis (-1 - 1)");
	if (axis.z < -1.0f || axis.z > 1.0f)
		runtime_error("Invalid obj axis (-1 - 1)");
	if (axis.x + axis.y + axis.z == 0)
		runtime_error("Invalid obj axis (-1 - 1)");
}

void	validate_color(t_color color)
{
	if (color.r < 0.0 || color.r > 255)
		runtime_error("Invalid light color values (0-255)");
	if (color.g < 0.0 || color.g > 255)
		runtime_error("Invalid light color values (0-255)");
	if (color.b < 0.0 || color.b > 255)
		runtime_error("Invalid light color values (0-255)");
}
