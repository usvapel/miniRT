#include "camera.h"
#include "minirt.h"

void	runtime_error(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
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

void	free_values(char **values[3], int count)
{
	int	i;

	i = 0;
	while (i < count)
		free_array((void *)values[i++]);
}

static t_vec3d	parse_vec3d(char **values[3], char **components)
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

static t_color	parse_color(char **values[3], char **components)
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

void	validate_camera(t_engine *engine)
{
	static bool is_initialized = false;

	if (engine->camera.fov < 0 || engine->camera.fov > 180)
		runtime_error("Invalid FOV value");
	if (engine->camera.dir.x < -1 || engine->camera.dir.x > 1)
		runtime_error("Invalid orientation x value");
	if (engine->camera.dir.y < -1 || engine->camera.dir.y > 1)
		runtime_error("Invalid orientation y value");
	if (engine->camera.dir.z < -1 || engine->camera.dir.z > 1)
		runtime_error("Invalid orientation z value");
	if (is_initialized)
		runtime_error("Too many cameras!");
	is_initialized = true;
}

char	**safe_split(char **values[3], int count, char *line)
{
	char	**splitted;

	if (!line)
		runtime_error("Possible invalid/missing values!");
	splitted = ft_split(line, ',');
	if (!splitted)
	{
		free_values(values, count);
		runtime_error("failure during memory allocation!");
	}
	return (splitted);
}

void	init_camera(t_engine *engine, char **split)
{
	char	**values[3];

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	if (split[4])
	{
		free_values(values, 3);
		runtime_error("too many values in camera!");
	}
	engine->camera.pos = parse_vec3d(values, values[0]);
	engine->camera.dir = parse_vec3d(values, values[1]);
	engine->camera.fov = ft_atof(values[2][0]);
	free_values(values, 3);
	validate_camera(engine);
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

void	init_light(t_vector *objects, char **split)
{
	const t_engine	*engine = get_engine();
	char			**values[3];
	t_light			*light;

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	light = malloc(sizeof(t_light));
	if (!light)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	light->base.type = LIGHT;
	light->base.pos = parse_vec3d(values, values[0]);
	light->brightness = ft_atof(values[1][0]);
	light->base.color = parse_color(values, values[2]);
	light->r = LIGHT_RADIUS;
	free_values(values, 3);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		runtime_error("Invalid light brightness value (0-1)");
	validate_color(light->base.color);
	add_elem(objects, light);
	add_elem(engine->lights, light);
}

void	init_sphere(t_vector *objects, char **split)
{
	char		**values[3];
	t_sphere	*sphere;

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	sphere->base.type = SPHERE;
	sphere->base.pos = parse_vec3d(values, values[0]);
	sphere->r = ft_atof(values[1][0]) / 2.0f;
	sphere->base.color = parse_color(values, values[2]);
	free_values(values, 3);
	validate_color(sphere->base.color);
	add_elem(objects, sphere);
}

void	init_plane(t_engine *engine, char **split)
{
	char	**values[3];
	t_plane	*plane;

	*values = NULL;
	values[0] = safe_split(values, 3, split[1]);
	values[1] = safe_split(values, 3, split[2]);
	values[2] = safe_split(values, 3, split[3]);
	plane = malloc(sizeof(t_plane));
	if (!plane)
	{
		free_values(values, 3);
		runtime_error("failure during memory allocation!");
	}
	plane->base.type = PLANE;
	plane->base.pos = parse_vec3d(values, values[0]);
	plane->normal = parse_vec3d(values, values[1]);
	plane->base.color = parse_color(values, values[2]);
	free_values(values, 3);
	validate_color(plane->base.color);
	if (plane->normal.x < -1.0f || plane->normal.x > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	if (plane->normal.y < -1.0f || plane->normal.y > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	if (plane->normal.z < -1.0f || plane->normal.z > 1.0f)
		runtime_error("Invalid plane normal (-1 - 1)");
	add_elem(engine->objects, plane);
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

void	init_cylinder(t_vector *objects, char **split)
{
	char		**values[5];
	t_cylinder	*cylinder;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
	{
		free_values(values, 5);
		runtime_error("failure during memory allocation!");
	}
	cylinder->base.type = CYLINDER;
	cylinder->base.pos = parse_vec3d(values, values[0]);
	cylinder->axis = parse_vec3d(values, values[1]);
	cylinder->r = ft_atof(values[2][0]) / 2;
	cylinder->h = ft_atof(values[3][0]);
	cylinder->base.color = parse_color(values, values[4]);
	cylinder->axis = normalize_vec3d(cylinder->axis);
	free_values(values, 5);
	validate_axis(cylinder->axis);
	validate_color(cylinder->base.color);
	add_elem(objects, cylinder);
}

void	init_paraboloid(t_vector *objects, char **split)
{
	char			**values[5];
	t_paraboloid	*para;

	*values = NULL;
	values[0] = safe_split(values, 5, split[1]);
	values[1] = safe_split(values, 5, split[2]);
	values[2] = safe_split(values, 5, split[3]);
	values[3] = safe_split(values, 5, split[4]);
	values[4] = safe_split(values, 5, split[5]);
	para = malloc(sizeof(t_paraboloid));
	if (!para)
	{
		free_values(values, 5);
		runtime_error("failure during memory allocation!");
	}
	para->base.type = PARABOLOID;
	para->base.pos = parse_vec3d(values, values[0]);
	para->axis = parse_vec3d(values, values[1]);
	para->focal = ft_atof(values[2][0]);
	para->h = ft_atof(values[3][0]);
	para->base.color = parse_color(values, values[4]);
	para->axis = normalize_vec3d(para->axis);
	free_values(values, 5);
	validate_axis(para->axis);
	validate_color(para->base.color);
	add_elem(objects, para);
}

void	set_values(t_engine *engine, char **split)
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

void	read_and_process_file(t_engine *engine, int fd)
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

char *check_file_validity(char *file)
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
