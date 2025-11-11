#include "minirt.h"

t_engine	*get_engine(void)
{
	static t_engine	engine;

	return (&engine);
}

t_object	*get_base_object(void *obj)
{
	return ((t_object *)obj);
}
