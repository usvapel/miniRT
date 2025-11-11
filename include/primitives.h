#ifndef PRIMITIVES_H
# define PRIMITIVES_H

# include "stdint.h"

typedef struct s_engine	t_engine;

typedef struct s_vec3d
{
	float				x;
	float				y;
	float				z;
}						t_vec3d;

typedef struct s_basis3d
{
	t_vec3d				up;
	t_vec3d				right;
	t_vec3d				forward;
}						t_basis3d;

typedef struct s_color
{
	float				r;
	float				g;
	float				b;
	float				a;
}						t_color;

// vec3d
t_vec3d					new_vec3d(float x, float y, float z);
void					scale_vec3d(t_vec3d *vec, float scaler);
t_vec3d					nscale_vec3d(t_vec3d vec, float scaler);
void					add_vec3d(t_vec3d *vec1, t_vec3d vec2);
void					minus_vec3d(t_vec3d *vec1, t_vec3d vec2);
void					print_vec(t_vec3d vec, char *id);
float					magnitude_vec3d(t_vec3d vec);
float					pow_magnitude_vec3d(t_vec3d vec);
void					normlize_vec3d(t_vec3d *vec);
t_vec3d					normalize_vec3d(t_vec3d vec);
float					dot_vec3d(t_vec3d vec, t_vec3d vec2);
t_vec3d					cross_vec3d(t_vec3d a, t_vec3d b);
t_vec3d					project_vec3d(t_vec3d vec, t_vec3d to);
t_vec3d					sub_vec3d(t_vec3d vec, t_vec3d vec2);
t_vec3d					add2_vec3d(t_vec3d vec, t_vec3d vec2);

// rotations
void					rotatex_vec3d(t_vec3d *vec, float angle);
void					rotatez_vec3d(t_vec3d *vec, float angle);
void					rotatey_vec3d(t_vec3d *vec, float angle);
void					rotatexyz_vec3d(t_vec3d *vec, float angle);
void					rotate_vec3d(t_vec3d *v, t_vec3d axis, float angle);

// local basis
t_vec3d					vec_in_basis(t_vec3d vec, t_basis3d basis);
t_vec3d					point_in_basis(t_vec3d vec, t_basis3d basis,
							t_vec3d origin);
t_vec3d					point_from_basis(t_vec3d vec, t_basis3d basis,
							t_vec3d origin);
t_basis3d				build_local_basis(t_vec3d up);
t_basis3d				build_tbn_basis(t_vec3d normal);

t_vec3d					multiply_vec3d(t_vec3d one, t_vec3d two);

// math utils
float					deg_to_radians(float angle);
float					smoothstep(float x);
float					smoothstep2(float x, float n);

// color utils
int						get_rgba(int r, int g, int b, int a);
void					apply_color(t_color *color, float brightness);
int						color_gradient(t_engine *engine, int y);
t_color					vec3d_to_color(t_vec3d v);
t_vec3d					color_to_vec3d(t_color c);
t_color					mix_colors(t_color c1, t_color c2, float r);
t_color					int_to_color(int c);
uint32_t				color_to_int(t_color color);

#endif // PRIMITIVES_H
