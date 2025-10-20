#ifndef CAMERA_H
# define CAMERA_H

#include "primitives.h"
#include "stdbool.h"

# define LEFT 0
# define RIGHT 1
# define CAM_SPEED 0.003
# define CAM_SENS 0.005

typedef struct s_engine t_engine;

typedef struct s_camera
{
	t_vec3d pos;
	t_vec3d dir;
	t_vec3d v;
	t_vec3d u;
	int fov;
}	t_camera;

void	update_camera(void);

#endif // CAMERA_H
