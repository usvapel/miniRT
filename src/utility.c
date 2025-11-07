#include "minirt.h"

void	get_screen_resolution(int32_t *width, int32_t *height)
{
	Display	*display;
	Screen	*screen;

	display = XOpenDisplay(NULL);
	if (display)
	{
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
