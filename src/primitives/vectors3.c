#include "minirt.h"

void	print_vec(t_vec3d vec, char *id)
{
	if (id)
		printf("%s ", id);
	printf("(%f, %f, %f)\n", vec.x, vec.y, vec.z);
}
