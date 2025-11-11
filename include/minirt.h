/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/11/11 14:20:23 by zfarah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include "camera.h"
# include "engine.h"
# include "geometry.h"
# include "libft.h"
# include "mlx_hooks.h"
# include "parsing.h"
# include "primitives.h"
# include "ray.h"
# include "textures.h"
# include "vector.h"
# include "viewport.h"
# include <errno.h>
# include <float.h>
# include <math.h>
# include <pthread.h>
# include <stdatomic.h>
# include <stdio.h>
# include <sys/time.h>

# define SHADOW_BIAS 0.2f
# define SHININESS 64.0f
# define X_AXIS 0
# define Y_AXIS 1
# define OBJ_SPEED 0.0003
# define OBJ_S_SPEED 0.0005
# define PI 3.14159265358979323846
# define QUALITY_DELAY_SECONDS 2

// phong
# define A_CONSTANT 1.0f
# define LINEAR_COEFFICIENT 0.09f
# define QUADRATIC_COEFFICIENT 0.032f

// needs cleaning in the future
t_engine	*get_engine(void);
float		clamp(float value, float min, float max);
void		cleanup_and_exit(void);
void		draw_scene(void *eng);
void		draw_to_buffer(t_threads *t, int x, int y, int color);
bool		timer(int prev_sec, int stop);
int			get_seconds(t_engine *engine);

void		phong_model(t_engine *engine, t_hit *hit);
int			objects_intersection(t_engine *engine, t_ray *ray, t_hit *hit);
bool		obj_intersection(void *obj, t_ray ray, t_hit *hit);

// phong
t_vec3d		reflect(t_vec3d direction, t_vec3d normal);

void		get_specular(t_engine *engine, t_hit *hit, t_phong *p,
				t_generic_light light);
void		get_diffuse(t_phong *p);

t_object	*get_base_object(void *obj);

// clean ups
void		cleanup_data(void);
void		cleanup_and_exit(void);

#endif // MINIRT_T
