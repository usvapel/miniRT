#include "minirt.h"

t_ray    get_ray(int x, int y);

void    raytracer(void *eng)
{
    t_engine *engine = (t_engine *)eng;
	t_sphere *spheres = *engine->objects;
    t_plane *plane = engine->objects[1];
    t_ray ray;
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
            sphere_hit(spheres[0], ray, &hit);
            if(hit.prev_hit)
                mlx_put_pixel(engine->image, x, y, scale_color(&hit.color, 1));
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
    t_vec3d tmp;

    p = ray.origin;
    tmp = ray.udir;
    scale_vec3d(&tmp, t);
    add_vec3d(&p, tmp);
    return p;
}