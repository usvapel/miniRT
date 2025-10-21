#ifndef PARSING_H
# define PARSING_H

# include "vector.h"
# include "engine.h"

void	runtime_error(char *s);
void	free_array(void **array);
void	free_values(char **values[3], int count);
char	**safe_split(char **values[3], int count, char *line);

t_vec3d	parse_vec3d(char **values[3], char **components);
t_color	parse_color(char **values[3], char **components);
void	validate_axis(t_vec3d axis);
void	validate_color(t_color color);

void	init_camera(t_engine *engine, char **split);
void	init_light(t_vector *objects, char **split);
void	init_sphere(t_vector *objects, char **split);
void	init_plane(t_engine *engine, char **split);
void	init_cylinder(t_vector *objects, char **split);
void	init_paraboloid(t_vector *objects, char **split);

#endif // PARSING_H
