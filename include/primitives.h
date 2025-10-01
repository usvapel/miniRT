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
	float r;
	float g;
	float b;
	float a;
} t_color;

// vec3d
t_vec3d new_vec3d(float x, float y, float z);
void scale_vec3d(t_vec3d *vec, float scaler);
void    add_vec3d(t_vec3d *vec1, t_vec3d vec2);
void    minus_vec3d(t_vec3d *vec1, t_vec3d vec2);
void    print_vec(t_vec3d vec, char *id);
float    magnitude_vec3d(t_vec3d vec);
float    pow_magnitude_vec3d(t_vec3d vec);
void    normlize_vec3d(t_vec3d *vec);
float dot_vec3d(t_vec3d vec, t_vec3d vec2);
void rotateX_vec3d(t_vec3d *vec, float angle);
void rotateZ_vec3d(t_vec3d *vec, float angle);
void rotateY_vec3d(t_vec3d *vec, float angle);


#endif
