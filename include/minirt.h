/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfarah <zfarah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 13:05:20 by jpelline          #+#    #+#             */
/*   Updated: 2025/10/01 16:02:35 by zfarah           ###   ########.fr       */
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
# include <sys/time.h>
# include <pthread.h>
# include <stdatomic.h>

// this is not allowed in the norm
#define deg_to_radians(degres) ((degres) * M_PI / 180.0)

typedef struct timeval t_time;
typedef pthread_t t_pthread;
typedef pthread_mutex_t	t_mutex;

# define THREAD_COUNT 8

typedef struct s_threads
{
	pthread_t		thread;
	int	index;
	int	start_y;
	int	end_y;
	int	start_x;
	int	end_x;
	atomic_bool	done;
}	t_threads;


typedef struct s_window
{
	int32_t	width;
	int32_t height;
	float	aspect_ratio;
}	t_window;

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
	void **objects;
	t_light  light;
	t_viewport viewport;
	atomic_bool update;
	double		mouse_x;
	double		mouse_y;

}	t_engine;

void input_parsing(t_engine *engine, char **av);
void color_background(t_engine *engine);
t_engine *get_engine(void);

void    update_viewport(t_viewport *viewport, t_window window);
int get_rgba(int r, int g, int b, int a);
int get_color(t_color *color);
uint32_t scale_color(t_color *color, float brightness);
void apply_color(t_color *color, float brightness);
void fps_counter(void *param);
void	key_hook(void *param);

void	cursor_hook(double x, double y, void *param);
float	solve_for_hit(t_ray ray, t_sphere sphere, float *t0, float *t1);
float	clamp(float value, float min, float max);
void	setup_threads(void *eng);
void wait_for_threads();
void	thread_cleanup();
void	cleanup_and_exit();
void	draw_scene(void *eng);
void wait_for_threads();
void    move_object(t_engine *engine);

#endif // MINIRT_T
