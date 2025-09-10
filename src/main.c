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

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	mlx_t *mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "asd", false);
	mlx_image_t *img = mlx_new_image(mlx, 200, 200);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
