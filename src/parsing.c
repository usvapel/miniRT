
#include "minirt.h"

void runtime_error(char *s)
{
	printf("Error: %s\n", s);
	exit(EXIT_FAILURE);
}

void free_array(void **array)
{
	void **copy;

	if (!array)
		return ;
	copy = array;
	while (*copy)
		free(*copy++);
	free(array);
}

void print_array(char **arr)
{
	while (*arr)
		ft_printf("%s ", *arr++);
}

static t_vec3d parse_vec3d(char **components)
{
	t_vec3d vec;

	vec.x = ft_atof(components[0]);
	vec.y = ft_atof(components[1]);
	vec.z = ft_atof(components[2]);
	return (vec);
}

void validate_camera(t_engine *engine)
{
	if (engine->camera.fov < 0 || engine->camera.fov > 180)
		runtime_error("Invalid FOV value");
	if (engine->camera.dir.x < -1 || engine->camera.dir.x > 1)
		runtime_error("Invalid orientation x value");
	if (engine->camera.dir.y < -1 || engine->camera.dir.y > 1)
		runtime_error("Invalid orientation y value");
	if (engine->camera.dir.z < -1 || engine->camera.dir.z > 1)
		runtime_error("Invalid orientation z value");
}

void free_values(char **values[3])
{
	int i = 0;
	while (i < 3)
		free_array( (void *) values[i++] );
}

char **safe_split(char **values[3], char *line)
{
	char **splitted;

	splitted = ft_split(line, ',');
	if (!splitted)
	{
		free_values(values);
		runtime_error("failure during memory allocation");
	}
	return (splitted);
}

void init_camera(t_engine *engine, char **split)
{
	char **values[3];

	*values = NULL;
	values[0] = safe_split(values, split[1]);
	values[1] = safe_split(values, split[2]);
	values[2] = safe_split(values, split[3]);
	engine->camera.pos = parse_vec3d(values[0]);
	engine->camera.dir = parse_vec3d(values[1]);
	engine->camera.fov = ft_atof(values[2][0]);
	free_values(values);
	validate_camera(engine);
}

int init_sp(t_engine *engine, char **split)
{
	char **values[3];

	values[0] = ft_split(split[1], ',');
	values[1] = ft_split(split[2], ',');
	values[2] = ft_split(split[3], ',');
	if (!values[0] || !values[1] || !values[2])
	{
		free_array( (void *) values[0] );
		free_array( (void *) values[1] );
		free_array( (void *) values[2] );
		exit(EXIT_FAILURE);
	}
	engine->sphere.type = SPHERE;
	engine->sphere.pos.x = ft_atof(values[0][1]);
	engine->sphere.pos.y = ft_atof(values[0][2]);
	engine->sphere.pos.z = ft_atof(values[0][3]);
	engine->sphere.diameter = ft_atof(values[1][0]);
	engine->sphere.color.r = ft_atof(values[2][0]);
	engine->sphere.color.g = ft_atof(values[2][1]);
	engine->sphere.color.b = ft_atof(values[2][2]);
	engine->sphere.color.a = 255;
	free_array( (void *) values[0] );
	free_array( (void *) values[1] );
	free_array( (void *) values[2] );
	return (0);
}

void set_values(t_engine *engine, char **split)
{
	if (!split[0])
		return ;
	// if (!ft_strcmp(split[1], "A"))
	// 	init_A(engine, split);
	if (ft_strcmp(split[0], "C") == 0)
		return (init_camera(engine, split));
	// init_L();
	// if (!ft_strcmp(split[1], "sp"))
	// if (ft_strcmp(split[0], "sp") == 0)
	// 	init_sp(engine, split);
	// init_pl();
	// init_cy();
	printf("invalid identifier: %s\n", split[0]);
}

void input_parsing(t_engine *engine, char **av)
{
	char *line;
	char **split;
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = ft_split(line, ' ');
		if (!split)
		{
			close(fd);
			free(line);
			free_array((void *)split);
			exit(EXIT_FAILURE);
		}
		free(line);
		set_values(engine, split);
		free_array((void *)split);
	}
	close(fd);
}
