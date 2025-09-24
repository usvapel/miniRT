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
    t_vec3d hit = {0};

    y = -1;
    while (++y < engine->window.height)
    {
        x = -1;
        while (++x < engine->window.width)
        {
            ray = get_ray(x, y);
            float color = sphere_ray_hit_test(ray, spheres[0]) * 1000;
            if (plane_hit(*plane, ray, &hit))
	            mlx_put_pixel(engine->image, x, y, scale_color(&plane->color, 1));
			if (sphere_hit(spheres[0], ray, &hit))
	            mlx_put_pixel(engine->image, x, y, get_rgba(color,color,color,color));

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

t_vec3d get_point_on_ray(t_ray ray, float t)
{
    t_vec3d p;

    p = ray.udir;
    scale_vec3d(&p, t);
    return p;
}