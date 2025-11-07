#include "minirt.h"

void	clean_textures(const t_engine *engine)
{
	int				i;
	t_image_text	*txt_data;

	txt_data = (((t_image_text *)engine->textures.images->data));
	if (engine->textures.images)
	{
		i = -1;
		while (++i < engine->textures.images->count)
		{
			free(txt_data[i].bump_source);
			free(txt_data[i].txt_source);
			if (txt_data[i].bump)
				mlx_delete_texture(txt_data[i].bump);
			mlx_delete_texture(txt_data[i].texture);
		}
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
	free_vector(engine->textures.checkers);
	free_vector(engine->textures.images);
	if (engine->scene_fd != -1)
		close(engine->scene_fd);
}
