/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/09/19 13:19:34 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include "camera.h"
# include "geometry.h"
# include "libft.h"
# include "primitives.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
typedef struct s_engine
{
	int32_t	monitor_width;
	int32_t monitor_height;
	mlx_t *mlx;
	mlx_image_t *image_background;
	mlx_image_t *objects;
	t_camera camera;
	t_sphere sphere;
}	t_engine;

void input_parsing(t_engine *engine, char **av);

#endif // MINIRT_T
