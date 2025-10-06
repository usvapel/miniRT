#include "minirt.h"

t_vector	*new_vector(size_t elem)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	if (!vector)
		exit(1);
	vector->data = malloc(sizeof(void *) * (elem * 2));
	vector->count = 0;
	vector->size = elem * 2;
	return (vector);
}

void	expand_vector(t_vector *vector)
{
	void	**new;
	size_t	i;

	i = 0;
	new = malloc(sizeof(void *) * (vector->size * 2 + 1));
	if (!new)
		exit(1);
	while (i < vector->count)
	{
		new[i] = vector->data[i];
		i++;
	}
	vector->data = new;
	vector->size *= 2;
	vector->data[vector->size] = NULL;
}

void	add_elem(t_vector *vector, void *elem)
{
	if (vector->count == vector->size - 1)
		expand_vector(vector);
	vector->data[vector->count] = elem;
	vector->count++;
}
