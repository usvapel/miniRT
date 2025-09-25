#include "minirt.h"

t_ray    get_ray(int x, int y);

float max(float val1, float val2)
{
	if (val1 > val2)
		return val1;
	if (val2 > val1)
		return val2;
	return val2;
}

void    raytracer(void *eng)
{
    t_engine *engine = (t_engine *)eng;
	t_sphere *spheres = *engine->objects;
	t_light light = engine->light;
    t_plane *plane = engine->objects[1];
    t_ray ray;
	t_vec3d pos = {0};
    int y;
    int x;
    t_hit hit;

    y = -1;
    while (++y < engine->window.height)
    {
        x = -1;
        while (++x < engine->window.width)
        {
            hit.prev_hit = false;
            ray = get_ray(x, y);
            plane_hit(*plane, ray, &hit);
            if (sphere_hit(spheres[0], ray, &hit))
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
            //if (hit.prev_hit)
	            //mlx_put_pixel(engine->image, x, y, scale_color(&hit.color, 1));
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
    minus_vec3d(&ray.udir, engine->camera.pos);
    return (ray);
}

t_vec3d get_point_on_ray(t_ray ray, float t)
{
    t_vec3d p;

    p = ray.udir;
    scale_vec3d(&p, t);
    return p;
}