#include "minirt.h"

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
	if (axis.x == 0 && axis.y == 0 && axis.z == 0)
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
