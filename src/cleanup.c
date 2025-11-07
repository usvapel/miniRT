#include "minirt.h"

void	clean_textures(const t_engine *engine)
{
	int	i;

	if (engine->textures.checkers)
	{
		i = -1;
		while (++i < engine->textures.checkers->count)
		{
			free(((t_image_text *)engine->textures.checkers->data)[i].bump_source);
			free(((t_image_text *)engine->textures.checkers->data)[i].txt_source);
			mlx_delete_texture(((t_image_text *)engine->textures.checkers->data)[i].bump);
			mlx_delete_texture(((t_image_text *)engine->textures.checkers->data)[i].texture);
		}
		free_vector(engine->textures.checkers);
	}
	if (engine->skybox.txt)
		mlx_delete_texture(engine->skybox.txt);
	free(engine->skybox.src);
	if (engine->image)
		mlx_delete_image(engine->mlx, engine->image);
	if (engine->image_buffer)
		mlx_delete_image(engine->mlx, engine->image_buffer);
}

void	cleanup_data(void)
{
	const t_engine	*engine = get_engine();

	clean_textures(engine);
	free_vector(engine->objects);
	free_vector(engine->g_lights);
	free_vector(engine->textures.images);
	close(engine->scene_fd);
}
