#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "engine.h"

void	runtime_error(char *s);
void	free_array(void **array);
void	free_values(char **values[], int count);
char	**safe_split(t_vector *v, char *line);
void	get_additional_values(t_vector *v, void *base, char **split, int index);

t_vec3d	parse_vec3d(t_vector *v, char **components);
t_color	parse_color(t_vector *v, char **components);
void	validate_axis(t_vec3d axis);
void	validate_color(t_color color);

void	init_ambient(char **split);
void	init_camera(t_engine *engine, char **split);
void	init_light(t_vector *objects, char **split);
void	init_spot_light(t_vector *objects, char **split);
void	init_sphere(t_vector *objects, char **split);
void	init_plane(t_engine *engine, char **split);
void	init_cylinder(t_vector *objects, char **split);
void	init_paraboloid(t_vector *objects, char **split);
void	init_cube(t_vector *objects, char **split);
void	init_checkerboard_text(t_vector *checkers, char **split);
void	init_image_text(t_vector *images, char **split);
void	link_texture(t_object *obj, char **split, int type);

void	autosave_scene(void);
void    save_light(t_generic_light l);
void    save_sphere(t_sphere sphere, t_object b);
void    save_cylinder(t_cylinder c, t_object b);
void    save_plane(t_plane p, t_object b);
void    save_paraboloid(t_paraboloid p, t_object b);
void    save_cube(t_cube c, t_object b);
void    save_additional_vals(t_object b);
void    save_texture(void *txt, t_texture_type type);
void    save_camera(t_camera c);
void    save_ampient(t_ambient a);

#endif // PARSING_H
