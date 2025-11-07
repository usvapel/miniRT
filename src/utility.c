#include "minirt.h"

int	handle_x_error(Display *display, XErrorEvent *error)
{
	(void)error;
	(void)display;
	return (0);
}

int	handle_io_error(Display *display)
{
	(void)display;
	exit(0);
}

void	get_screen_resolution(int32_t *width, int32_t *height)
{
	Display	*display;
	Screen	*screen;

	display = XOpenDisplay(NULL);
	if (display)
	{
		XSetErrorHandler(handle_x_error);
		XSetIOErrorHandler(handle_io_error);
		screen = DefaultScreenOfDisplay(display);
		*width = screen->width;
		*height = screen->height;
		XCloseDisplay(display);
	}
	else
	{
		*width = 1920;
		*height = 1080;
	}
}
