#include "minirt.h"

void	auto_save_objects(t_vector *objects);
void	auto_save_textures(t_textures textures);
void	auto_save_lights(t_vector lights, t_ambient ambient);
void	auto_save_skybox(t_skybox skybox);

void	autosave_scene(void)
{
	const t_engine	*engine = get_engine();
	int				fd;

	fd = open(engine->scene, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		close(fd);
		return ;
	}
	save_camera(engine->camera);
	auto_save_lights(*engine->g_lights, engine->ambient);
	auto_save_objects(engine->objects);
	auto_save_textures(engine->textures);
	auto_save_skybox(engine->skybox);
	close(fd);
}

void	auto_save_lights(t_vector lights, t_ambient ambient)
{
	int	i;

	i = -1;
	printf("\n# Lights\n");
	save_ambient(ambient);
	while (++i < lights.count)
		save_light(*((t_generic_light *)lights.data[i]));
}

void	auto_save_objects(t_vector *objects)
{
	t_object	b;
	void		*obj;
	int			i;

	printf("\n# Objects\n");
	i = -1;
	while (++i < objects->count)
	{
		obj = objects->data[i];
		b = *get_base_object(obj);
		if (b.type == SPHERE)
			save_sphere(*((t_sphere *)obj), b);
		else if (b.type == CYLINDER)
			save_cylinder(*((t_cylinder *)obj), b);
		else if (b.type == PLANE)
			save_plane(*((t_plane *)obj), b);
		else if (b.type == PARABOLOID)
			save_paraboloid(*((t_paraboloid *)obj), b);
		else if (b.type == CUBE)
			save_cube(*((t_cube *)obj), b);
	}
}

void	auto_save_textures(t_textures textures)
{
	int	i;

	printf("\n# Texture images\n");
	i = -1;
	while (++i < textures.images->count)
		save_texture(textures.images->data[i], IMAGE);
	i = -1;
	printf("\n# Texture checkerboards\n");
	while (++i < textures.checkers->count)
		save_texture(textures.checkers->data[i], CHECKERBOARD);
}

void	auto_save_skybox(t_skybox skybox)
{
	printf("\n# Skybox images\n");
	if (skybox.txt)
		printf("sky %s", skybox.src);
	printf("\n");
}
