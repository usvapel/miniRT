#include "minirt.h"

/*
	R = L - 2(N * L),
		where N is normal surface and L is the incoming vector
		from the light source to the hit
*/
t_vec3d	reflect(t_vec3d direction, t_vec3d normal)
{
	float	dot;
	t_vec3d	tmp;

	dot = dot_vec3d(direction, normal);
	tmp = nscale_vec3d(normal, dot);
	tmp = nscale_vec3d(tmp, 2);
	tmp = sub_vec3d(direction, tmp);
	return (tmp);
}

/*
	S = (V * R)^n, where V is view and R is the reflection of the light
*/
void	get_specular(t_engine *engine, t_hit *hit, t_phong *p,
		t_generic_light light)
{
	float	specular_strength;
	float	light_distance;

	p->view_dir = sub_vec3d(engine->camera.pos, hit->pos);
	p->view_dir = normalize_vec3d(p->view_dir);
	p->reflect_dir = reflect(nscale_vec3d(p->nlight_dir, -1.0f), p->normal);
	p->reflect_dir = normalize_vec3d(p->reflect_dir);
	specular_strength = powf(fmaxf(0.0f, dot_vec3d(p->view_dir,
					p->reflect_dir)), SHININESS);
	p->specular = nscale_vec3d(p->light_color, specular_strength);
	light_distance = magnitude_vec3d(sub_vec3d(adjusted_light_pos(light),
				hit->pos));
	p->specular = nscale_vec3d(p->specular, 1.0f / (light_distance));
}

void	get_diffuse(t_phong *p)
{
	float	distance;
	float	shadow;

	distance = magnitude_vec3d(p->nlight_dir);
	shadow = A_CONSTANT / (A_CONSTANT + LINEAR_COEFFICIENT * distance
			+ QUADRATIC_COEFFICIENT * distance * distance);
	p->diffuse_strength = dot_vec3d(p->normal, p->nlight_dir);
	p->diffuse_strength = fmaxf(0.0f, p->diffuse_strength);
	p->diffuse = nscale_vec3d(multiply_vec3d(p->light_color, p->model_color),
			p->diffuse_strength * shadow);
}
