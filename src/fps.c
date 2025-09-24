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


void add_fps(char *title, int fps)
{
	int i = 0;
	int j = 0;
	int start = 14;
	int temp = fps;
	char buf[6];

	if (fps == 0)
	{
		title[start] = '0';
		title[start + 1] = '\0';
		return ;
	}
	while (temp > 0 && i < 5)
	{
		buf[i++] = (temp % 10) + '0';
		temp /= 10;
	}
	while (j < i)
	{
		title[start + j] = buf[i - j - 1];
		j++;
	}
	title[start + i] = '\0';
}

void fps_counter(void *param)
{
	t_engine *engine;
	static int fps;
	static int prev_sec;
	int curr_sec;
	char title[20] = "MiniRT | fps: ";

	engine = param;
	curr_sec = get_seconds(engine);
	if (curr_sec > prev_sec)
	{
		add_fps(title, fps);
		mlx_set_window_title(engine->mlx, title);
		fps = 0;
	}
	fps++;
	prev_sec = curr_sec;

}
