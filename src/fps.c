
#include "minirt.h"

int	get_seconds(t_engine *engine)
{
	t_time		now;
	long long	us;
	long		ms;

	gettimeofday(&now, NULL);
	us = ((long long)now.tv_sec * 1000000 + now.tv_usec);
	us = us - ((long long)engine->start.tv_sec * 1000000 + engine->start.tv_usec);
	ms = us / 1000000;
	return ((int)ms);
}

void fps_counter(void *param)
{
	t_engine *engine;
	static int fps;
	static int prev_sec;
	int curr_sec;

	engine = param;
	curr_sec = get_seconds(engine);
	if (curr_sec > prev_sec)
	{
		printf("fps: %d\n", fps);
		fps = 0;
	}
	fps++;
	prev_sec = curr_sec;

}
