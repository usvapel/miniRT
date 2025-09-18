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

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_engine *engine;

	engine = param;
	if (keydata.action == MLX_PRESS)
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(engine->mlx);
}

void print_values(t_engine *engine)
{
	printf("%f ", engine->camera.pos.x);
	printf("%f ", engine->camera.pos.y);
	printf("%f\n", engine->camera.pos.z);
	printf("%f ", engine->camera.dir.x);
	printf("%f ", engine->camera.dir.y);
	printf("%f\n", engine->camera.dir.z);
	printf("%f\n", engine->camera.fov);
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
	print_values(engine);
	free(engine);
	return 0;
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
