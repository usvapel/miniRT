/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/10/22 13:54:38 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include "mlx_hooks.h"

# include "engine.h"
# include "libft.h"
# include "primitives.h"
# include "ray.h"
# include "camera.h"
# include "viewport.h"
# include "light.h"
# include "geometry.h"
# include "vector.h"
# include "parsing.h"
# include "textures.h"

# include <errno.h>
# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <float.h>
# include <stdatomic.h>

// this is not allowed in the norm
#define deg_to_radians(degres) ((degres) * M_PI / 180.0)

# define SHADOW_BIAS 0.2f
# define SHININESS 64.0f
# define X_AXIS 0
# define Y_AXIS 1
# define ESPSILON 1e-2
# define OBJ_SPEED 0.00003
# define OBJ_S_SPEED 0.0005

// needs cleaning in the future
void		input_parsing(t_engine *engine, char **av);
int			color_gradient(t_engine *engine, int y);
t_engine	*get_engine(void);
int		get_rgba(int r, int g, int b, int a);
uint32_t	scale_color(t_color *color, float brightness);
void	apply_color(t_color *color, float brightness);
float	clamp(float value, float min, float max);
void	cleanup_and_exit();
void	draw_scene(void *eng);
bool	timer(int prev_sec, int stop);
int		get_seconds(t_engine *engine);
t_color	checker_board(t_hit *hit);
float	max(float val1, float val2);
t_color	vec3d_to_color(t_vec3d v);
t_vec3d	color_to_vec3d(t_color c);
void	phong_model(t_engine *engine, t_hit *hit);
int		object_intersection(t_engine *engine, t_ray *ray, t_hit *hit);

// threads
void	setup_threads(void *eng);
void	wait_for_threads();
void	thread_cleanup();

// phong
t_vec3d	reflect(t_vec3d direction, t_vec3d normal);

t_color int_to_color(int c);
#endif // MINIRT_T
