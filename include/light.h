
#ifndef LIGHT_H
# define LIGHT_H

# include "minirt.h"

typedef struct s_light
{
	int		type;
	t_vec3d pos;
	float	brightness;
	t_color color;
} t_light;

#endif
