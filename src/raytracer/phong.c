#include "minirt.h"

static t_vec3d	reflect(t_vec3d direction, t_vec3d normal)
{
	float	dot;
	t_vec3d	tmp;

	dot = dot_vec3d(direction, normal);
	tmp = nscale_vec3d(normal, dot);
	scale_vec3d(&tmp, 2);
	minus_vec3d(&direction, tmp);

	return (direction);
}

static void	get_specular(t_engine *engine, t_hit *hit, t_phong p)
{
	float	specular_strength;

	p.view_dir = sub_vec3d(engine->camera.pos, hit->pos);
	normlize_vec3d(&p.view_dir);
	p.reflect_dir = reflect(nscale_vec3d(p.light_dir, -1.0f), p.normal);
	normlize_vec3d(&p.reflect_dir);
	specular_strength = powf(max(0.0f, dot_vec3d(p.view_dir, p.reflect_dir)), 10.0f);
	p.specular = nscale_vec3d(p.light_color, specular_strength);
}

static void	get_diffuse(t_phong *p)
{
	float	distance;
	float	attenuation;

	distance = magnitude_vec3d(p->light_dir);
	p->light_dir = normalize_vec3d(p->light_dir);
	attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);
	p->diffuse_strength = dot_vec3d(p->normal, p->light_dir);
	p->diffuse_strength = fmaxf(0.0f, p->diffuse_strength);
	p->diffuse = nscale_vec3d(multiply_vec3d(p->light_color, p->model_color), p->diffuse_strength * attenuation);
}

static bool	is_in_shadow(t_phong p, t_engine *engine, t_hit hit, t_light *light)
{
	t_ray	shadow_ray = {0};
	t_hit	shadow_hit = {0};
	t_vec3d	tmp;
	float	light_distance;
	float	object_distance;
	
	tmp = normalize_vec3d(hit.normal);
	shadow_ray.origin = add2_vec3d(hit.pos, nscale_vec3d(tmp, SHADOW_BIAS));
	shadow_ray.udir = light->pos;
	light_distance = magnitude_vec3d(p.light_dir);
	shadow_hit.prev_hit = false;
	(void)object_intersection(engine, &shadow_ray, &shadow_hit);
	object_distance = magnitude_vec3d(sub_vec3d(shadow_hit.pos, hit.pos));
	if (shadow_hit.prev_hit && shadow_hit.type != LIGHT && object_distance < light_distance)
		return (true);
	return (false);
}

// float	smoothstep(float x)
// {
//   return (x * x * ( 3.0 - 2.0 * x));
// }

void	phong_model(t_engine *engine, t_hit *hit)
{
	t_light	*light;
	t_phong	p = {0};
	int	i;

	if (hit->type == LIGHT)
		return ;
	p.model_color = color_to_vec3d(hit->color);
	p.ambient = nscale_vec3d(p.model_color, 0.1);
	p.normal = normalize_vec3d(hit->normal);
	p.final_color = p.ambient;
	i = 0;
	while (i < engine->light_count)
	{
		light = engine->lights->data[i++];
		p.light_color = color_to_vec3d(light->color);
		p.light_dir = sub_vec3d(light->pos, hit->pos);
		if (is_in_shadow(p, engine, *hit, light))
			continue ;
		get_diffuse(&p);
		get_specular(engine, hit, p);
		p.diffuse = nscale_vec3d(p.diffuse, 0.4f);
		p.final_color = add2_vec3d(p.final_color, p.diffuse);
		p.final_color = add2_vec3d(p.final_color, p.specular);
	}
	hit->color = vec3d_to_color(p.final_color);
}
