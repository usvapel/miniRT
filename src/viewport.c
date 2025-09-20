#include "minirt.h"

void    update_viewport(t_viewport *viewport, t_window window);
void    set_pixal_spacing(t_viewport *viewport);
void    set_starting_pixel(t_viewport *viewport);

void    setup_viewport(void)
{
    t_engine *engine;
    
    engine = get_engine();
    update_viewport(&engine->viewport, engine->window);
}

void    update_viewport(t_viewport *viewport, t_window window)
{	
    const t_engine *engine = get_engine();
    const float fov = engine->camera.fov;
    viewport->h = 2 * tan(deg_to_radians(fov / 2));
    viewport->w = window.aspect_ratio * viewport->h;
    viewport->hori_axis = new_vec3d(viewport->w, 0, 0);
    viewport->vert_axis = new_vec3d(0, -viewport->h, 0);
    set_pixal_spacing(viewport);
    set_starting_pixel(viewport);
    print_vec(viewport->step_x, "Step-x: ");
    print_vec(viewport->step_y, "Step-y: ");
    print_vec(viewport->start_pixel, "Starting: ");
}


void set_pixal_spacing(t_viewport *viewport)
{
    const t_window window = get_engine()->window;
    const float hori_scaler = 1 / (float) window.height;
    const float vert_scaler = 1 / (float) window.height;
    
    viewport->step_x = viewport->hori_axis;;
    viewport->step_y = viewport->vert_axis;;
    scale_vec3d(&viewport->step_x, hori_scaler);
    scale_vec3d(&viewport->step_y, vert_scaler);
}

void    set_starting_pixel(t_viewport *viewport)
{
    const t_camera camera = get_engine()->camera;
    const t_vec3d focal_vec = new_vec3d(0, 0, FOCAL_LENGTH);
    t_vec3d top_left;
    t_vec3d tmp;
    // starting position
    top_left = camera.pos;
    add_vec3d(&top_left, focal_vec);
    // move backwards half the distance of viewport's horizental axis
    tmp = viewport->hori_axis;
    scale_vec3d(&tmp, 0.5);
    minus_vec3d(&top_left, tmp);
    // move upwards half the distance of viewport's vertical axis
    tmp = viewport->vert_axis;
    scale_vec3d(&tmp, 0.5);
    minus_vec3d(&top_left, tmp);
    // from top left position move half the distance of the horizental pixal spacing to the right
    viewport->start_pixel = top_left;
    tmp = viewport->step_x;
    scale_vec3d(&tmp, 0.5);
    add_vec3d(&viewport->start_pixel, tmp);
    // from top left position move half the distance of the vertical pixal spacing to the bottom
    tmp = viewport->step_y;
    scale_vec3d(&tmp, 0.5);
    add_vec3d(&viewport->start_pixel, tmp);
}
