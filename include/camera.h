#ifndef CAMERA_H
# define CAMERA_H

# include "primitives.h"

typedef struct s_camera
{
	t_vec3d pos;
	t_vec3d dir;
	int fov;
} t_camera;

#endif
