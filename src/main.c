#include "minirt.h"

t_engine *get_engine()
{
	static t_engine engine;

	return (&engine);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_engine	*engine;

	engine = param;
	if (keydata.action == MLX_PRESS)
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(engine->mlx);
}

void	print_values(t_engine *engine)
{
	printf("camera\n");
	print_vec(engine->camera.pos, "Camera-pos: ");
	print_vec(engine->camera.dir, "Camera-dir: ");
	printf("Camera-fov: %d\n", engine->camera.fov);

	printf("sphere\n");

	print_vec(engine->sphere.pos, "Sphere: ");
	printf("%f\n", engine->camera.dir.z);
	printf("sphere-type: %d\n", engine->sphere.type);
	printf("sphere-r-%f\n", engine->sphere.r);
	printf("%d ", engine->sphere.color.r);
	printf("%d ", engine->sphere.color.g);
	printf("%d ", engine->sphere.color.b);
	printf("%d\n", engine->sphere.color.a);


	printf("light\n");
	printf("%f\n", engine->light.pos.x);
	printf("%f\n", engine->light.pos.y);
	printf("%f\n", engine->light.pos.z);
	printf("%f\n", engine->light.brightness);
	printf("%d\n", engine->light.color.r);
	printf("%d\n", engine->light.color.g);
	printf("%d\n", engine->light.color.b);
	printf("%d\n", engine->light.color.a);
}

int	main(int ac, char **av)
{
	t_engine	*engine;

	if (ac < 2)
		return (0);
	engine = get_engine();
	input_parsing(engine, av);
	print_values(engine);
	mlx_set_setting(MLX_HEADLESS, true);
	engine->mlx = mlx_init(10, 10, "miniRT", true);
    mlx_get_monitor_size(0, &engine->window.width, &engine->window.height);
	engine->window.aspect_ratio = (float)engine->window.width / engine->window.height;
	mlx_terminate(engine->mlx);
	print_vec(engine->sphere.pos, "Sphere");
	setup_viewport();
	mlx_set_setting(MLX_HEADLESS, false);
	engine->mlx = mlx_init(engine->window.width, engine->window.height, "miniRT", true);
	engine->image = mlx_new_image(engine->mlx, engine->window.width, engine->window.height);
	mlx_image_to_window(engine->mlx, engine->image, 0, 0);
	color_background(engine);
	mlx_key_hook(engine->mlx, key_hook, engine);
	mlx_loop_hook(engine->mlx, raytracer, engine);
	mlx_loop(engine->mlx);
	mlx_terminate(engine->mlx);
	return (0);
}
