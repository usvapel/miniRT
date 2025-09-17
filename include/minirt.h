#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42.h>
# include <errno.h>
# include <math.h>
# include <stdio.h>
# include "camere.h"
# include "geometry.h"
# include "libft.h"
# include "primitives.h"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800

typedef struct s_engine
{
	int32_t		monitor_width;
	int32_t		monitor_height;
	mlx_t		*mlx;
	mlx_image_t	*image_background;
	mlx_image_t	*objects;
	t_camera	*camera;
}				t_engine;

#endif
