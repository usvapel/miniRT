/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/10/17 14:36:14 by zfarah           ###   ########.fr       */
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
# include "camera.h"
# include "viewport.h"
# include "light.h"
# include "geometry.h"
# include "vector.h"
# include <sys/time.h>
# include <pthread.h>
#include <float.h>
# include <stdatomic.h>

// this is not allowed in the norm
#define deg_to_radians(degres) ((degres) * M_PI / 180.0)

typedef struct timeval t_time;
typedef pthread_t t_pthread;
typedef pthread_mutex_t	t_mutex;

# define THREAD_COUNT 12
# define SHADOW_BIAS 0.001f
# define X_AXIS 0
# define Y_AXIS 1

typedef struct s_phong
{
	t_vec3d model_color;
	t_vec3d ambient;
	t_vec3d light_color;
	t_vec3d light_dir;
	t_vec3d normal;
	t_vec3d diffuse;
	t_vec3d specular;
	t_vec3d final_color;
	t_vec3d view_dir;
	t_vec3d reflect_dir;
	float diffuse_strength;
}	t_phong;

typedef struct s_threads
{
	pthread_t		thread;
	int	index;
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
	atomic_bool	done;
	atomic_bool end;
	atomic_int block_size;
	bool last_move;
}	t_threads;


typedef struct s_window
{
	int32_t	width;
	int32_t height;
	float	aspect_ratio;
}	t_window;

typedef struct s_mouse
{
	t_vec3d pos;
	t_vec3d	prev_pos;
}	t_mouse;

typedef struct s_engine
{
	t_window window;
	t_threads threads[THREAD_COUNT];
	t_mutex lock;
	atomic_bool recalculate;
	mlx_t *mlx;
	mlx_image_t *image;
	mlx_image_t *image_buffer;
	t_time start;
	t_camera camera;
	t_vector *objects;
	t_vector  *lights;
	int	object_count;
	int light_count;
	t_viewport viewport;
	atomic_bool update;
	atomic_bool moving;
	atomic_int  last_move_time;
	int fps;
	t_mouse mouse;
	t_phong p;
}	t_engine;

void		input_parsing(t_engine *engine, char **av);
int			color_gradient(t_engine *engine, int y);
t_engine	*get_engine(void);

void	update_viewport(t_viewport *viewport, t_window window);
int		get_rgba(int r, int g, int b, int a);
int		get_color(t_color *color);
uint32_t	scale_color(t_color *color, float brightness);
void	apply_color(t_color *color, float brightness);
void	fps_counter(void *param);
void	key_hook(void *param);
void	cursor_hook(double x, double y, void *param);
float	solve_for_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
float	clamp(float value, float min, float max);
void	setup_threads(void *eng);
void	wait_for_threads();
void	thread_cleanup();
void	cleanup_and_exit();
void	draw_scene(void *eng);
void	wait_for_threads();
void    scale_object(void *obj, double x, double y);
void move_object(void *obj, t_ray ray, float dx, float dy);
void *inside_object(t_ray *ray, double x, double y, int *type);
void    move_pos_left_right(t_camera *cam, t_vec3d *pos, float d);
bool	timer(int prev_sec, int stop);
int		get_seconds(t_engine *engine);
t_color	checker_board(t_hit *hit);
float	max(float val1, float val2);
t_color	vec3d_to_color(t_vec3d v);
t_vec3d	color_to_vec3d(t_color c);
void	phong_model(t_engine *engine, t_hit *hit);
int		object_intersection(t_engine *engine, t_ray *ray, t_hit *hit);
t_vec3d	get_point_on_ray(t_ray ray, float t);
t_ray	get_ray(int x, int y);

#endif // MINIRT_T
