#include "minirt.h"

t_ray    get_ray(int x, int y);

void    raytracer(void *eng)
{
    t_engine *engine = (t_engine *)eng;
    t_ray ray;
    int y;
    int x;

    y = -1;
    while (++y < engine->window.height)
    {
        x = -1;
        while (++x < engine->window.width)
        {
            ray = get_ray(x, y);
            if (sphere_ray_hit(ray, engine->sphere))
                mlx_put_pixel(engine->image, x, y, 0x43ff64d9);

            //compute ray intersections with objects in the world
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
    //normlize_vec3d(&ray.udir);
    return (ray);
}