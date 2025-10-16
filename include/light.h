#ifndef LIGHT_H
# define LIGHT_H

# include "primitives.h"
# include <stdbool.h>
# include "ray.h"

typedef struct s_light
{
	int		type;
	t_vec3d pos;
	float r;
	float	brightness;
	t_color color;
} t_light;

bool light_hit(t_light light, t_ray ray, t_hit *hit);

#endif // LIGHT_H
