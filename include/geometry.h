#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "primitives.h"

typedef struct s_sphere
{
	int type;
	t_vec3d pos;
	float diameter;
	t_color color;
} t_sphere;

typedef enum e_id
{
	AMBIENT_LIGHNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
} t_id ;

#endif