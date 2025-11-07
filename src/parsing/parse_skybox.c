#include "minirt.h"

void	init_skybox(char **split)
{
	t_engine	*engine;

	engine = get_engine();
	if (engine->skybox.txt || !split[1])
		return ;
	printf("Initializing skybox: %s\n", split[1]);
	engine->skybox.txt = mlx_load_png(split[1]);
	if (!engine->skybox.txt)
		runtime_error(ft_strjoin("failed to load ", split[1]));
	engine->skybox.src = ft_strdup(split[1]);
}
