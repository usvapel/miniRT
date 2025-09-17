/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:04:43 by jpelline          #+#    #+#             */
/*   Updated: 2025/09/09 14:40:07 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

void init_C(t_engine *engine, char **split)
{
	char **pos[3];

	pos[0] = ft_split(split[1], ',');
	pos[1] = ft_split(split[2], ',');
	pos[2] = ft_split(split[3], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		free_array( (void *) pos[0] );
		free_array( (void *) pos[1] );
		free_array( (void *) pos[2] );
		exit(EXIT_FAILURE);
	}
	engine->camera.pos.x = ft_atof(pos[0][0]);
	engine->camera.pos.y = ft_atof(pos[0][1]);
	engine->camera.pos.z = ft_atof(pos[0][2]);
	engine->camera.dir.x = ft_atof(pos[1][0]);
	engine->camera.dir.y = ft_atof(pos[1][1]);
	engine->camera.dir.z = ft_atof(pos[1][2]);
	engine->camera.fov = ft_atof(pos[2][0]);
	free_array( (void *) pos[0] );
	free_array( (void *) pos[1] );
	free_array( (void *) pos[2] );
}

void init_sp(t_engine *engine, char **split)
{
	char **pos[3];

	pos[0] = ft_split(split[1], ',');
	pos[1] = ft_split(split[2], ',');
	pos[2] = ft_split(split[3], ',');
	if (!pos[0] || !pos[1] || !pos[2])
	{
		free_array( (void *) pos[0] );
		free_array( (void *) pos[1] );
		free_array( (void *) pos[2] );
		exit(EXIT_FAILURE);
	}
	engine->sphere.type = SPHERE;
	engine->sphere.pos.x = ft_atof(pos[0][1]);
	engine->sphere.pos.y = ft_atof(pos[0][2]);
	engine->sphere.pos.z = ft_atof(pos[0][3]);
	engine->sphere.diameter = ft_atof(pos[1][0]);
	engine->sphere.color.r = ft_atof(pos[2][0]);
	engine->sphere.color.g = ft_atof(pos[2][1]);
	engine->sphere.color.b = ft_atof(pos[2][2]);
	engine->sphere.color.a = 255;
	free_array( (void *) pos[0] );
	free_array( (void *) pos[1] );
	free_array( (void *) pos[2] );
}

void set_values(t_engine *engine, char **split)
{
	if (!split[0])
		return ;
	// if (!ft_strcmp(split[1], "A"))
	// 	init_A(engine, split);
	print_array(split);
	if (ft_strcmp(split[1], "C") == 0)
		init_C(engine, split);
	// init_L();
	// if (!ft_strcmp(split[1], "sp"))
	if (ft_strcmp(split[1], "sp") == 0)
		init_sp(engine, split);
	// init_pl();
	// init_cy();
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

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_engine *engine;

	engine = param;
	if (keydata.action == MLX_PRESS)
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(engine->mlx);
}

int main(int ac, char **av)
{
	t_engine *engine;

	if (ac < 2)
		return (0);
	engine = ft_calloc(1, sizeof(t_engine));
	if (!engine)
		return (1);
	input_parsing(engine, av);
	mlx_set_setting(MLX_HEADLESS, true);
	engine->mlx = mlx_init(10, 10, "miniRT", true);
    mlx_get_monitor_size(0, &engine->monitor_width, &engine->monitor_height);
	mlx_terminate(engine->mlx);
	mlx_set_setting(MLX_HEADLESS, false);
	engine->mlx = mlx_init(engine->monitor_width, engine->monitor_height, "miniRT", true);
	engine->image_background = mlx_new_image(engine->mlx, engine->monitor_width, engine->monitor_height);
	mlx_image_to_window(engine->mlx, engine->image_background, 0, 0);
	mlx_key_hook(engine->mlx, key_hook, engine);
	mlx_loop(engine->mlx);
	mlx_terminate(engine->mlx);
	free(engine);
	return (0);
}
