#include "minirt.h"

void auto_save_lights(t_generic_light light);
void    auto_save_objects(void *obj);
void save_sphere(t_sphere sphere, t_object b);
void save_cylinder(t_cylinder c, t_object b);
void save_plane(t_plane p, t_object b);
void save_paraboloid(t_paraboloid p, t_object b);
void save_cube(t_cube c, t_object b);
void    save_additional_vals(t_object b);

void autosave_scene(void)
{
    const t_engine *engine = get_engine();
    const int fd = open(engine->scene, O_WRONLY | O_CREAT | O_TRUNC);
    const t_camera c = engine->camera; 
    const t_ambient a = engine->ambient;
    int i;

    if (fd < 0)
        return;
    i = -1;
    (void)i;
    dup2(fd, STDOUT_FILENO);
    printf("C  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %d\n\n", c.pos.x, c.pos.y,c.pos.z, c.dir.x, c.dir.y,c.dir.z, c.fov);
    printf("A  %.1f  %.0f,%.0f,%.0f\n\n", a.ratio, a.base.color.r, a.base.color.g, a.base.color.b);
    while (++i < engine->g_lights->count)
        auto_save_lights(*((t_generic_light *)engine->g_lights->data[i]));
    i = -1;
    while (++i < engine->objects->count)
        auto_save_objects(engine->objects->data[i]);
    close(fd);
    exit(1);
}

void auto_save_lights(t_generic_light l)
{
    const t_object b = l.base;
    t_spot_light s;

    if (b.type == POINT_LIGHT)
    {
        printf("L  %.1f,%.1f,%.1f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, l.brightness, b.color.r, b.color.g, b.color.b);
        if (l.obj_index >= 0)
            printf("obj %d\n", l.obj_index);
        else
            printf("\n");
    }
    if (b.type == SPOT_LIGHT)
    {
        s = l.spot_light;
        printf("LS  %.1f,%.1f,%.1f  %.1f,%.1f,%1.f  %.1f  %.1f  %.0f  %.0f,%.0f,%.0f  ",
            b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, l.brightness,s.range, s.fov, b.color.r, b.color.g, b.color.b);
        if (l.obj_index >= 0)
            printf("obj %d\n", l.obj_index);
        else
            printf("\n");
    }
}


void    auto_save_objects(void *obj)
{
    const t_object b = *get_base_object(obj);
    if (b.type == SPHERE)
        save_sphere(*((t_sphere *)obj), b);
    else if (b.type == CYLINDER)
        save_cylinder(*((t_cylinder *)obj), b);
    else if (b.type == PLANE)
        save_plane(*((t_plane *)obj), b);
    else if (b.type == PARABOLOID)
        save_paraboloid(*((t_paraboloid *)obj), b);
    else if (b.type == CUBE)
        save_cube(*((t_cube *)obj), b);

}

void save_sphere(t_sphere s, t_object b)
{
    printf("sp  %.1f,%.1f,%.1f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, s.r + s.r, b.color.r, b.color.g, b.color.b);
    save_additional_vals(b);
}
void save_cylinder(t_cylinder c, t_object b)
{
    printf("cy  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.1f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, c.r, c.h, b.color.r, b.color.g, b.color.b);
    save_additional_vals(b);
}
void save_plane(t_plane p, t_object b)
{
    (void)p;
    printf("pl  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, b.color.r, b.color.g, b.color.b);
    save_additional_vals(b);
}
void save_paraboloid(t_paraboloid p, t_object b)
{
    printf("pa  %.1f,%.1f,%.1f  %.1f,%.1f,%.1f  %.1f  %.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, b.axis->x, b.axis->y, b.axis->z, p.focal, p.h, b.color.r, b.color.g, b.color.b);
    save_additional_vals(b);
}
void save_cube(t_cube c, t_object b)
{
    printf("cu  %.1f,%.1f,%.1f  %.1f  %.1f  %.1f,%.1f,%.1f  %.0f,%.0f,%.0f  ", b.pos.x, b.pos.y, b.pos.z, c.w, c.h, b.axis->x, b.axis->y, b.axis->z,b.color.r, b.color.g, b.color.b);
    save_additional_vals(b);
}
void    save_additional_vals(t_object b)
{
    if (b.material.reflect > 0)
        printf("rl %1.f  ", b.material.reflect);
    if (b.material.refract > 0)
        printf("rf %1.f  ", b.material.refract);
    if (b.texture.index > -1 && b.texture.type == CHECKERBOARD)
        printf("ch %d", b.texture.index);
    if (b.texture.index > -1 && b.texture.type == IMAGE)
        printf("img %d", b.texture.index);
    printf("\n");
}
char *type(t_id type)
{
    if (type == SPOT_LIGHT)
        return "LS";
    if (type == SPHERE)
        return "s";
    if (type == CYLINDER)
        return "cy";
    if (type == PARABOLOID)
        return "pa";
    if (type == CUBE)
        return "cu";
    if (type == PLANE)
        return "pl";
    return NULL;
}
