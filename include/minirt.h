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
# include "primitives.h"
# include "ray.h"
# include "geometry.h"
# include "camera.h"
# include "viewport.h"
# include "light.h"

// this is not allowed in the norm
#define deg_to_radians(degres) ((degres) * M_PI / 180.0)

typedef struct s_window
{
	int32_t	width;
	int32_t height;
	float	aspect_ratio;
}	t_window;

typedef struct s_engine
{
	t_window window;
	mlx_t *mlx;
	mlx_image_t *image;
	t_camera camera;
	void **objects;
	t_light  light;
	t_viewport viewport;
}	t_engine;

void input_parsing(t_engine *engine, char **av);
void color_background(t_engine *engine);
t_engine *get_engine(void);
float sphere_ray_hit_test(t_ray ray, t_sphere sphere);

void    update_viewport(t_viewport *viewport, t_window window);
int get_rgba(int r, int g, int b, int a);
int get_color(t_color *color);
int scale_color(t_color *color, float brightness);
#endif // MINIRT_T
