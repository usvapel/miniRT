#ifndef MLX_HOOKS_H
# define MLX_HOOKS_H

#include "primitives.h"
#include "stdbool.h"
#include "ray.h"
#include "camera.h"

typedef struct s_engine t_engine;

// key hook
void	key_hook(void *param);

// camera movement
void handle_cam_movement(t_engine *engine);

// objects movement
void move_objects(t_engine *engine);
void *inside_object(t_ray *ray, double x, double y, int *type);

// objects scaling
void scale_objects(t_engine *engine);

// fps counter
void	fps_counter(void *param);

long	time_in_ms(void);

#endif // mlx_hooks_H
