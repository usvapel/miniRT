/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpelline <jpelline@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/09/15 15:00:47 by jpelline         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <math.h>
# include "libft.h"
# include <MLX42.h>
# include "MLX42.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

typedef struct s_camera t_camera;
typedef struct s_color t_color;
typedef struct s_vec3d t_vec3d;
typedef enum e_id t_id;

typedef struct s_engine
{
	int32_t	monitor_width;
	int32_t monitor_height;
	mlx_t *mlx;
	mlx_image_t *image_background;
	mlx_image_t *objects;
	t_camera *camera;
}	t_engine;

typedef struct s_camera
{
	t_vec3d *pos;
	t_vec3d *dir;
	int fov;
} t_camera;

typedef struct s_sphere
{
	int type;
	t_vec3d *pos;
	float diameter;
	t_color *color;
} t_sphere;

typedef struct s_vec3d
{
	float x;
	float y;
	float z;
} t_vec3d;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int a;
} t_color;

typedef enum e_id
{
	AMBIENT_LIGHNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
} t_id ;
#endif // MINIRT_T
