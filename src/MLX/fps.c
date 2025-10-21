#include "minirt.h"

long	time_in_ms(void)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	return (start.tv_sec * 1000L + (start.tv_usec / 1000L));
}

int	get_seconds(t_engine *engine)
{
	t_time		now;
	long long	us;
	long		ms;

	gettimeofday(&now, NULL);
	us = ((long long)now.tv_sec * 1000000 + now.tv_usec);
	us = us - ((long long)engine->frame.start.tv_sec * 1000000 + engine->frame.start.tv_usec);
	ms = us / 1000000;
	return ((int)ms);
}

bool	timer(int prev_sec, int stop)
{
	t_engine *engine = get_engine();
	int curr_sec;

	curr_sec = get_seconds(engine);
	if (curr_sec > (prev_sec + stop))
		return (true);
	return (false);
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
	static int prev_sec;
	int curr_sec;
	char title[20] = "MiniRT | fps: ";

	engine = param;
	curr_sec = get_seconds(engine);
	if (curr_sec > prev_sec)
	{
		add_fps(title, engine->frame.fps);
		mlx_set_window_title(engine->mlx, title);
		engine->frame.fps = 0;
	}
	prev_sec = curr_sec;
}
