#include "minirt.h"
#include "primitives.h"

t_vec3d reflect(t_vec3d direction, t_vec3d normal)
{
	float dot;
	t_vec3d tmp;

	dot = dot_vec3d(direction, normal);
	tmp = nscale_vec3d(normal, dot);
	scale_vec3d(&tmp, 2);
	minus_vec3d(&direction, tmp);

	return (direction);
}

void get_specular(t_engine *engine, t_hit *hit, t_phong p)
{
	float specular_strength;

	p.view_dir = sub_vec3d(engine->camera.pos, hit->pos);
	normlize_vec3d(&p.view_dir);
	p.reflect_dir = reflect(nscale_vec3d(p.light_dir, -1.0f), p.normal);
	normlize_vec3d(&p.reflect_dir);
	specular_strength = powf(max(0.0f, dot_vec3d(p.view_dir, p.reflect_dir)), 10.0f);
	p.specular = nscale_vec3d(p.light_color, specular_strength);
}

bool is_in_shadow(t_phong p, t_engine *engine, t_vec3d hit_pos)
{
	t_ray shadow_ray = {0};
	t_hit hit = {0};
	
	hit.prev_hit = false;
	t_vec3d tmp = p.light_dir;
	normlize_vec3d(&tmp);
	shadow_ray.origin = add2_vec3d(hit_pos, nscale_vec3d(tmp, 0.001f));
	shadow_ray.udir = tmp;
	float light_distance = magnitude_vec3d(p.light_dir);
	(void)object_intersection(engine, &shadow_ray, &hit);
	float object_distance = magnitude_vec3d(sub_vec3d(hit.pos, hit_pos));
	if (hit.prev_hit && hit.type != LIGHT && object_distance < light_distance)
		return (true);
	return (false);
}

void phong_model(t_engine *engine, t_hit *hit)
{
	int i;
	t_light *light;
	t_phong p = {0};

	if (hit->type == LIGHT)
		return ;
	p.model_color = color_to_vec3d(hit->color);
	p.ambient = nscale_vec3d(p.model_color, 0.1);
	p.normal = hit->normal;
	normlize_vec3d(&p.normal);
	p.final_color = p.ambient;
	i = 0;
	while (i < engine->light_count)
	{
		light = engine->lights->data[i++];
		p.light_color = color_to_vec3d(light->color);
		p.light_dir = sub_vec3d(light->pos, hit->pos);
		float distance = magnitude_vec3d(p.light_dir);
		if (is_in_shadow(p, engine, hit->pos))
			continue ;
		normlize_vec3d(&p.light_dir);
		float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);
		p.diffuse_strength = max(0.0, dot_vec3d(p.normal, p.light_dir));
		p.diffuse = nscale_vec3d(multiply_vec3d(p.light_color, p.model_color), p.diffuse_strength * attenuation);
		get_specular(engine, hit, p);
		scale_vec3d(&p.specular, 0.08f);
		p.final_color = add2_vec3d(p.final_color, p.diffuse);
		p.final_color = add2_vec3d(p.final_color, p.specular);
	}
	hit->color = vec3d_to_color(p.final_color);
}
