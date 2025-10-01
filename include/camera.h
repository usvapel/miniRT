#ifndef CAMERA_H
# define CAMERA_H

# include "minirt.h"

# define LEFT 0
# define RIGHT 1

typedef struct s_engine t_engine;

typedef struct s_camera
{
	t_vec3d pos;
	t_vec3d dir;
	t_vec3d v;
	int fov;
} t_camera;


void 	update_camera(void);
void    look_up_down(t_camera *camera, float dy);
void    orient_camera(t_engine *engine, float nx, float ny);
void    move_camera(mlx_key_data_t keydata, t_engine *engine);

#endif
