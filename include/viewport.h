#ifndef VIEWPORT_H
# define VIEWPORT_H

# include "primitives.h"

# define FOCAL_LENGTH 1

typedef struct s_viewport
{
	float w;
	float h;
	float aspect_ratio;
	t_vec3d hori_axis;
	t_vec3d vert_axis;
	t_vec3d start_pixel;
	t_vec3d step_x;
	t_vec3d step_y;
}	t_viewport;

void	setup_viewport(void);
t_vec3d	get_viewport_pixel(int x, int y);;

#endif // VIEWPORT_H
