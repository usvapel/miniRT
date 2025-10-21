#include "minirt.h"

t_vec3d	parse_vec3d(char **values[3], char **components)
{
	t_vec3d	vec;

	if (!components[0] || !components[1] || !components[2])
	{
		free_values(values, 3);
		runtime_error("invalid/missing values!");
	}
	vec.x = ft_atof(components[0]);
	vec.y = ft_atof(components[1]);
	vec.z = ft_atof(components[2]);
	return (vec);
}

t_color	parse_color(char **values[3], char **components)
{
	t_color	color;

	if (!components[0] || !components[1] || !components[2])
	{
		free_values(values, 3);
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

static void	set_values(t_engine *engine, char **split)
{
	if (!split[0])
		return ;
	if (ft_strcmp(split[0], "C") == 0)
		return (init_camera(engine, split));
	if (ft_strcmp(split[0], "L") == 0)
		return (init_light(engine->objects, split));
	if (ft_strcmp(split[0], "sp") == 0)
		return (init_sphere(engine->objects, split));
	if (ft_strcmp(split[0], "pl") == 0)
		return (init_plane(engine, split));
	if (ft_strcmp(split[0], "cy") == 0)
		return (init_cylinder(engine->objects, split));
	if (ft_strcmp(split[0], "pa") == 0)
		return (init_paraboloid(engine->objects, split));
}

static void	read_and_process_file(t_engine *engine, int fd)
{
	char	*line;
	char	**split;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			line[ft_strlen(line) - 1] = 0;
		split = ft_split(line, ' ');
		if (!split)
		{
			close(fd);
			free(line);
			runtime_error("failure during memory allocation!");
		}
		set_values(engine, split);
		free_array((void *)split);
		free(line);
	}
	close(fd);
}

static char	*check_file_validity(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strncmp(file + len - 3, ".rt", len - 3) == 0)
		return (file);
	return (NULL);
}

void	input_parsing(t_engine *engine, char **av)
{
	int		fd;

	engine->objects = new_vector(1);
	engine->objects->owns_data = true;
	engine->lights = new_vector(1);
	engine->lights->owns_data = false;
	fd = open(check_file_validity(av[1]), O_RDONLY);
	if (fd < 0)
		runtime_error("failure opening file!");
	read_and_process_file(engine, fd);
}
