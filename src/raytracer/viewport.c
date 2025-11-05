#include "minirt.h"

void    update_viewport(t_viewport *viewport, t_window window);
void    set_pixal_spacing(t_viewport *viewport);
void    set_starting_pixel(t_viewport *viewport);

void	setup_viewport(void)
{
    t_engine	*engine;
    
    engine = get_engine();
    update_viewport(&engine->viewport, engine->window);
}

void	update_viewport(t_viewport *viewport, t_window window)
{	
	const t_vec3d		vu = new_vec3d(0,1,0);
	t_engine	*engine;
	int	fov;
	t_vec3d		w;
	
	engine = get_engine();
	fov = engine->camera.fov;
	w = nscale_vec3d(engine->camera.dir, -1);
	engine->camera.u = cross_vec3d(w, vu);
	engine->camera.v = cross_vec3d(w, engine->camera.u);
	viewport->w = 2 * tan(deg_to_radians(fov / 2));
	viewport->h = viewport->w / window.aspect_ratio;
	viewport->hori_axis = engine->camera.u;
	viewport->vert_axis = engine->camera.v;
	scale_vec3d(&viewport->hori_axis, viewport->w);
	scale_vec3d(&viewport->vert_axis, viewport->h);
	set_pixal_spacing(viewport);
	set_starting_pixel(viewport);
}


void	set_pixal_spacing(t_viewport *viewport)
{
	const	t_window window = get_engine()->window;
	const	float hori_scaler = 1 / (float) window.width;
	const	float vert_scaler = 1 / (float) window.height;

	viewport->step_x = viewport->hori_axis;;
	viewport->step_y = viewport->vert_axis;;
	scale_vec3d(&viewport->step_x, hori_scaler);
	scale_vec3d(&viewport->step_y, vert_scaler);
}

void	set_starting_pixel(t_viewport *viewport)
{
	const t_camera camera = get_engine()->camera;
	const t_vec3d focal_vec = camera.dir;
	t_vec3d top_left;
	t_vec3d tmp;

	top_left = camera.pos;
	add_vec3d(&top_left, focal_vec);
	tmp = viewport->hori_axis;
	scale_vec3d(&tmp, 0.5);
	minus_vec3d(&top_left, tmp);
	tmp = viewport->vert_axis;
	scale_vec3d(&tmp, 0.5);
	minus_vec3d(&top_left, tmp);
	viewport->start_pixel = top_left;
	tmp = viewport->step_x;
	scale_vec3d(&tmp, 0.5);
	add_vec3d(&viewport->start_pixel, tmp);
	tmp = viewport->step_y;
	scale_vec3d(&tmp, 0.5);
	add_vec3d(&viewport->start_pixel, tmp);
}

t_vec3d	get_viewport_pixel(int x, int y)
{
	const	t_engine *engine = get_engine();
	t_vec3d	pixel;
	t_vec3d	step;

	pixel = engine->viewport.start_pixel;
	step = engine->viewport.step_x;
	scale_vec3d(&step, x);
	add_vec3d(&pixel, step);

	step = engine->viewport.step_y;
	scale_vec3d(&step, y);
	add_vec3d(&pixel, step);
	return (pixel);
}
