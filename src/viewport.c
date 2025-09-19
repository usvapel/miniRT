#include "minirt.h"

void    setup_viewport(void)
{
    t_engine *engine;
    t_viewport viewport;
    
    engine = get_engine();
    viewport = engine->viewport;
    viewport.h = 2;
    viewport.hori_axis = new_vec3d(viewport.w, 0, 0);
    viewport.vert_axis = new_vec3d(0, -viewport.h, 0);
   
    adjust_with_to_camera();
}

void    adjust_with_to_camera()
{
    t_engine *engine;
    t_camera *camera;
    t_viewport viewport;
    t_vec3d top_left;
    
    engine = get_engine();
    camera = engine->camera;
    viewport.aspect_ratio = engine->monitor_width / engine->monitor_height;
    viewport.w = viewport.aspect_ratio * viewport.h;
    viewport.step_x = new_vec3d(viewport.hori_axis.x / engine->monitor_width,
        viewport.hori_axis.y / engine->monitor_width,
        viewport.hori_axis.z / engine->monitor_width);
    viewport.step_y = new_vec3d(viewport.vert_axis.x / engine->monitor_height,
        viewport.vert_axis.y / engine->monitor_height,
        viewport.vert_axis.z / engine->monitor_height);
    top_left = *camera->pos;
    add_vec3d(&top_left, new_vec3d())
}