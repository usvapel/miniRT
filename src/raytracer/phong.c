#include "minirt.h"

static void	accumulate_transparency(t_phong *p, t_vec3d *shadow,
		t_ray *shadow_ray, t_hit *shadow_hit)
{
	*shadow = color_to_vec3d(vec3d_to_color(*shadow));
	shadow_ray->origin = add2_vec3d(shadow_hit->pos, nscale_vec3d(p->nlight_dir,
				EPSILON));
	*shadow = nscale_vec3d(*shadow, shadow_hit->material.refract);
}

static t_vec3d	get_shadow_attenuation(t_phong *p, t_engine *engine, t_hit hit,
		t_generic_light light)
{
	t_hit	shadow_hit;
	float	light_distance;
	t_vec3d	shadow;
	t_ray	shadow_ray;

	shadow_ray = (t_ray){0};
	shadow = (t_vec3d){1.0, 1.0, 1.0};
	shadow_ray.origin = add2_vec3d(hit.pos, nscale_vec3d(p->nlight_dir,
				EPSILON));
	shadow_ray.udir = p->nlight_dir;
	light_distance = magnitude_vec3d(sub_vec3d(adjusted_light_pos(light),
				shadow_ray.origin));
	while (true)
	{
		shadow_hit = (t_hit){0};
		objects_intersection(engine, &shadow_ray, &shadow_hit);
		if (!shadow_hit.prev_hit
			|| get_base_object(shadow_hit.obj)->is_light_source
			|| magnitude_vec3d(sub_vec3d(shadow_hit.pos,
					shadow_ray.origin)) > light_distance)
			return (shadow);
		if (shadow_hit.material.refract == -1)
			return ((t_vec3d){0});
		accumulate_transparency(p, &shadow, &shadow_ray, &shadow_hit);
	}
}

static void	accumulate_colors(t_phong *p, t_generic_light *light,
		t_vec3d shadow)
{
	p->diffuse = nscale_vec3d(p->diffuse, light->brightness);
	p->specular = nscale_vec3d(p->specular, light->brightness);
	p->diffuse = multiply_vec3d(p->diffuse, shadow);
	p->specular = multiply_vec3d(p->specular, shadow);
	p->final_color = add2_vec3d(p->final_color, p->diffuse);
	p->final_color = add2_vec3d(p->final_color, p->specular);
}

static void	loop_through_lights(t_phong *p, t_engine *engine, t_hit *hit)
{
	t_generic_light	*light;
	t_object		*base;
	t_vec3d			shadow;
	int				i;

	i = 0;
	while (i < engine->g_lights->count)
	{
		light = engine->g_lights->data[i++];
		base = get_base_light(light);
		p->light_color = color_to_vec3d(base->color);
		p->nlight_dir = normalize_vec3d(sub_vec3d(base->pos, hit->pos));
		if (base->type == SPOT_LIGHT && !spot_light_hit(light, hit, p))
			continue ;
		shadow = get_shadow_attenuation(p, engine, *hit, *light);
		if (shadow.x < EPSILON && shadow.y < EPSILON && shadow.z < EPSILON)
			continue ;
		get_diffuse(p);
		if (hit->type != PLANE && hit->type != CUBE)
			get_specular(engine, hit, p, *light);
		accumulate_colors(p, light, shadow);
	}
}

void	phong_model(t_engine *engine, t_hit *hit)
{
	t_phong	p;

	if (get_base_object(hit->obj)->is_light_source)
		return ;
	p.model_color = color_to_vec3d(hit->color);
	p.ambient = color_to_vec3d(engine->ambient.base.color);
	p.final_color = nscale_vec3d(p.ambient, engine->ambient.ratio);
	p.normal = hit->normal;
	loop_through_lights(&p, engine, hit);
	hit->color = vec3d_to_color(p.final_color);
}
