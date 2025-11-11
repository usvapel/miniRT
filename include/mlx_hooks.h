#ifndef MLX_HOOKS_H
# define MLX_HOOKS_H

# include "camera.h"
# include "geometry.h"
# include "primitives.h"
# include "ray.h"
# include "stdbool.h"

typedef struct s_engine	t_engine;

// init
void					initialize_mlx(t_engine *engine);

// key hook
void					key_hook(void *param);

// resize hook
void					resize_screen(int window_width, int window_height,
							void *eng);

// camera movement
void					handle_cam_movement(t_engine *engine);

// objects movement
void					move_objects(t_engine *engine);
void					*inside_object(t_ray *ray, double x, double y);

// objects scaling
void					scale_objects(t_engine *engine);
void					scale_cube(t_cube *cube, float dx, float dy, float dt);
void					scale_paraboloid(t_paraboloid *para, float dx, float dy,
							float dt);
void					scale_cylinder(t_cylinder *cy, float dx, float dy,
							float dt);
void					scale_sphere(t_sphere *sphere, float dx, float dt);

// objects rotation
void					rotate_objects(t_engine *engine);

// fps counter
void					fps_counter(void *param);

long					time_in_ms(void);

#endif // MLX_HOOKS_H
