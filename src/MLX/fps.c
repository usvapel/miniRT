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
	us = us - ((long long)engine->frame.start.tv_sec * 1000000
			+ engine->frame.start.tv_usec);
	ms = us / 1000000;
	return ((int)ms);
}

bool	timer(int prev_sec, int stop)
{
	t_engine	*engine;
	int			curr_sec;

	engine = get_engine();
	curr_sec = get_seconds(engine);
	if (curr_sec > (prev_sec + stop))
		return (true);
	return (false);
}

void	add_fps(char *title, int fps)
{
	int		i;
	int		j;
	int		start;
	int		temp;
	char	buf[6];

	start = 14;
	temp = fps;
	if (fps == 0)
	{
		title[start] = '0';
		title[start + 1] = '\0';
		return ;
	}
	i = 0;
	while (temp > 0 && i < 5)
	{
		buf[i++] = (temp % 10) + '0';
		temp /= 10;
	}
	j = -1;
	while (++j < i)
		title[start + j] = buf[i - j - 1];
	title[start + i] = '\0';
}

void	fps_counter(void *param)
{
	t_engine	*engine;
	static int	prev_sec;
	int			curr_sec;
	static char	title[20] = "MiniRT | fps: ";

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
