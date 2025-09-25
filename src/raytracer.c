#include "minirt.h"
#include "primitives.h"

t_ray    get_ray(int x, int y);

float max(float val1, float val2)
{
	if (val1 > val2)
		return val1;
	if (val2 > val1)
		return val2;
	return val2;
}


float map(float value, float in_max, float out_min, float out_max)
{
	return (value * (out_max - out_min) / in_max + out_min);
}

void    raytracer(void *eng)
{
    t_engine *engine = (t_engine *)eng;
	t_sphere *spheres = *engine->objects;
	t_light light = engine->light;
    t_ray ray;
	t_vec3d pos = {0};
    int y;
    int x;
	bool hit;

    y = -1;
    while (++y < engine->window.height)
    {
        x = -1;
        while (++x < engine->window.width)
        {
            ray = get_ray(x, y);
			hit = sphere_hit(spheres[0], ray, &pos);
			if (hit)
			{
				t_vec3d tmp = new_vec3d(pos.x, pos.y, pos.z);
				minus_vec3d(&pos, spheres[0].pos);
				t_vec3d light_dir = new_vec3d(light.pos.x, light.pos.y, light.pos.z);
				minus_vec3d(&light_dir, tmp);
				normlize_vec3d(&light_dir);
				normlize_vec3d(&pos);
				float d = max(dot_vec3d(pos, light_dir), 0.0f);
				mlx_put_pixel(engine->image, x, y, scale_color(&spheres[0].color, d));
			}
        }
    }
}

t_ray    get_ray(int x, int y)
{
    const t_engine *engine = get_engine();
    const t_vec3d pixel = get_viewport_pixel(x, y);
    t_ray ray;

    ray.origin = engine->camera.pos;
    ray.udir = pixel;
    minus_vec3d(&ray.udir, ray.origin);
    return (ray);
}
