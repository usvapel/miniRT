#include "minirt.h"

static void	set_values(t_engine *engine, char **split)
{
	if (!split[0])
		return ;
	if (ft_strcmp(split[0], "A") == 0)
		return (init_ambient(split));
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
	if (ft_strcmp(split[0], "tx") == 0 && ft_strcmp(split[1], "ch") == 0)
		return (init_checkerboard_text(engine->textures.checkers, split));
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
	engine->textures.checkers = new_vector(1);
	fd = open(check_file_validity(av[1]), O_RDONLY);
	if (fd < 0)
		runtime_error("failure opening file!");
	read_and_process_file(engine, fd);
}
