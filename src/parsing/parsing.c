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
		return (init_light(engine->g_lights, split));
	if (ft_strcmp(split[0], "LS") == 0)
		return (init_spot_light(engine->g_lights, split));
	if (ft_strcmp(split[0], "sp") == 0)
		return (init_sphere(engine->objects, split));
	if (ft_strcmp(split[0], "pl") == 0)
		return (init_plane(engine, split));
	if (ft_strcmp(split[0], "cy") == 0)
		return (init_cylinder(engine->objects, split));
	if (ft_strcmp(split[0], "pa") == 0)
		return (init_paraboloid(engine->objects, split));
	if (ft_strcmp(split[0], "cu") == 0)
		return (init_cube(engine->objects, split));
	if (ft_strcmp(split[0], "tx") == 0 && ft_strcmp(split[1], "ch") == 0)
		return (init_checkerboard_text(engine->textures.checkers, split));
	if (ft_strcmp(split[0], "tx") == 0 && ft_strcmp(split[1], "img") == 0)
		return (init_image_text(engine->textures.images, split));
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

static void	map_lights_to_objects(t_vector *objects, t_vector *g_lights)
{
	t_generic_light	*light;
	t_object		*base;
	t_object		*obj_base;
	int				i;

	i = 0;
	puts("map lights to objects");
	while (i < g_lights->count)
	{
		light = g_lights->data[i++];
		base = get_base_object(light);
		if (light->obj_index < 0)
			continue ;
		light->obj = objects->data[light->obj_index];
		obj_base = get_base_object(light->obj);
		obj_base->pos = base->pos;
		obj_base->is_light_source = base->type == POINT_LIGHT;
		obj_base->semi_light_source = base->type == SPOT_LIGHT;
		if (obj_base->axis)
			base->axis = obj_base->axis;
	}
}

void	input_parsing(t_engine *engine, char **av)
{
	int	fd;

	engine->objects = new_vector(1);
	engine->g_lights = new_vector(1);
	engine->textures.checkers = new_vector(1);
	engine->textures.images = new_vector(1);
	engine->scene = av[1];
	engine->autosave = av[2] && !ft_strcmp(av[2], "--autosave");
	fd = open(check_file_validity(av[1]), O_RDONLY);
	if (fd < 0)
		runtime_error("failure opening file!");
	read_and_process_file(engine, fd);
	map_lights_to_objects(engine->objects, engine->g_lights);
}
