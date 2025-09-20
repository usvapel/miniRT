#ifndef PRIMITIVES_H
# define PRIMITIVES_H

typedef struct s_vec3d
{
	float x;
	float y;
	float z;
} t_vec3d;

typedef struct s_color
{
	int r;
	int g;
	int b;
	int a;
} t_color;

// vec3d
t_vec3d new_vec3d(float x, float y, float z);
void scale_vec3d(t_vec3d *vec, float scaler);
void    add_vec3d(t_vec3d *vec1, t_vec3d vec2);
void    minus_vec3d(t_vec3d *vec1, t_vec3d vec2);
void    print_vec(t_vec3d vec, char *id);


#endif
