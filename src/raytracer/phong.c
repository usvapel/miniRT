#include "minirt.h"

# define A_CONSTANT 1.0f
# define LINEAR_COEFFICIENT 0.09f
# define QUADRATIC_COEFFICIENT 0.032f

/*
	R = L - 2(N * L), where N is normal surface and L is the incoming vector from the light source to the hit
*/
static t_vec3d	reflect(t_vec3d direction, t_vec3d normal)
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
static void	get_specular(t_engine *engine, t_hit *hit, t_phong *p)
{
	float	specular_strength;

	p->view_dir = sub_vec3d(engine->camera.pos, hit->pos);
	p->view_dir = normalize_vec3d(p->view_dir);
	p->reflect_dir = reflect(nscale_vec3d(p->nlight_dir, -1.0f), p->normal);
	p->reflect_dir = normalize_vec3d(p->reflect_dir);
	specular_strength = powf(fmaxf(0.0f, dot_vec3d(p->view_dir, p->reflect_dir)), SHININESS);
	p->specular = nscale_vec3d(p->light_color, specular_strength);
}

static void	get_diffuse(t_phong *p)
{
	float	distance;
	float	attenuation;

	distance = magnitude_vec3d(p->light_dir);
	p->light_dir = normalize_vec3d(p->light_dir);
	attenuation = A_CONSTANT / (A_CONSTANT + LINEAR_COEFFICIENT * distance
				+ QUADRATIC_COEFFICIENT * distance * distance);
	p->diffuse_strength = dot_vec3d(p->normal, p->light_dir);
	p->diffuse_strength = fmaxf(0.0f, p->diffuse_strength);
	p->diffuse = nscale_vec3d(multiply_vec3d(p->light_color, p->model_color), p->diffuse_strength * attenuation);
}

static bool	is_in_shadow(t_phong *p, t_engine *engine, t_hit hit, t_light light)
{
	t_ray	shadow_ray = {0};
	t_hit	shadow_hit = {0};
	float	light_distance;
	float	object_distance;
	
	shadow_ray.origin = add2_vec3d(hit.pos, nscale_vec3d(p->nlight_dir, 1e-2));
	shadow_ray.udir = p->nlight_dir;
	(void)object_intersection(engine, &shadow_ray, &shadow_hit);
	if (!shadow_hit.prev_hit || shadow_hit.type == LIGHT)
		return (false);
	light_distance = magnitude_vec3d(sub_vec3d(light.base.pos, shadow_ray.origin));
	object_distance = magnitude_vec3d(sub_vec3d(shadow_hit.pos, shadow_ray.origin));
	if ((object_distance + ESPSILON) < light_distance)
		return (true);
	return (false);
}

void	phong_model(t_engine *engine, t_hit *hit)
{
	t_light	*light;
	t_phong	p = {0};
	int	i;

	if (hit->type == LIGHT)
		return ;
	p.model_color = color_to_vec3d(hit->color);
	p.ambient = new_vec3d(0.1, 0.1, 0.1);
	p.normal = normalize_vec3d(hit->normal);
	p.final_color = p.ambient;
	i = 0;
	while (i < engine->light_count)
	{
		light = engine->lights->data[i++];
		p.light_color = color_to_vec3d(light->base.color);
		p.light_dir = sub_vec3d(light->base.pos, hit->pos);
		p.nlight_dir = normalize_vec3d(p.light_dir);
		if (is_in_shadow(&p, engine, *hit, *light))
			continue ;
		get_diffuse(&p);
		get_specular(engine, hit, &p);
		if (hit->type == PLANE)
			p.specular = nscale_vec3d(p.specular, 0.0f);
		p.diffuse = nscale_vec3d(p.diffuse, light->brightness);
		p.specular = nscale_vec3d(p.specular, light->brightness);
		p.final_color = add2_vec3d(p.final_color, p.diffuse);
		p.final_color = add2_vec3d(p.final_color, p.specular);
	}
	hit->color = vec3d_to_color(p.final_color);
}
