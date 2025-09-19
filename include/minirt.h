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

# include "MLX42.h"
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include "libft.h"
# include "camera.h"
# include "geometry.h"
# include "primitives.h"

typedef struct s_window
{
	int32_t	width;
	int32_t height;
	int32_t	aspect_ratio;
}	t_window;

typedef struct s_engine
{
	t_window window;
	mlx_t *mlx;
	mlx_image_t *image;
	t_camera camera;
	t_sphere sphere;
}	t_engine;

void input_parsing(t_engine *engine, char **av);

#endif // MINIRT_T
