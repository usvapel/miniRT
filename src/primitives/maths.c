#include "minirt.h"

float	deg_to_radians(float angle)
{
	return ((angle) * M_PI / 180.0);
}

float	smoothstep(float x)
{
	return (x * x * x / (3.0 * x * x - 3.0 * x + 1.0));
}

float	smoothstep2(float x, float n)
{
	return (pow(x, n) / (pow(x, n) + pow(1.0 - x, n)));
}
