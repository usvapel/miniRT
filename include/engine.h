#ifndef ENGINE_H
# define ENGINE_H

# include "MLX42.h"
# include "primitives.h"
# include <stdbool.h>
# include <pthread.h>
# include <stdatomic.h>
# include <sys/time.h>
# include "camera.h"
# include "viewport.h"
# include "vector.h"
# include "geometry.h"
# include "textures.h"

typedef struct timeval t_time;
typedef pthread_t t_pthread;
typedef pthread_mutex_t	t_mutex;

# define THREAD_COUNT 12
# define PIXEL_BLOCK_SIZE 5

typedef struct s_phong
{
	t_vec3d model_color;
	t_vec3d ambient;
	t_vec3d light_color;
	t_vec3d light_dir;
	t_vec3d nlight_dir;
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

typedef struct s_frame
{
	int fps;
	long delta;
	long t_last_frame;
	t_time start;
} t_frame;

typedef struct s_engine
{
	t_window window;
	t_threads threads[THREAD_COUNT];
	t_mutex lock;
	atomic_bool recalculate;
	mlx_t *mlx;
	mlx_image_t *image;
	mlx_image_t *image_buffer;
	t_camera camera;
	t_ambient ambient;
	t_vector *objects;
	t_vector  *lights;
	t_textures  textures;
	t_viewport viewport;
	atomic_bool update;
	atomic_bool moving;
	atomic_int  last_move_time;
	atomic_bool complete_img;
	t_frame frame;
	t_mouse mouse;
	t_phong p;
}	t_engine;

#endif // ENGINE_H
