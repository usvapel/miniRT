#include "minirt.h"

void	init_skybox(char **split)
{
    t_engine *engine = get_engine();

    if (engine->skybox || !split[1])
        return;
	printf("Initializing skybox: %s\n", split[1]);
	engine->skybox = mlx_load_png(split[1]);
	if (!engine->skybox)
		runtime_error(ft_strjoin("failed to load ", split[1]));
}
