#include "minirt.h"

t_vector	*new_vector(size_t elem)
{
	t_vector	*vector;

	if (elem == 0)
		elem = 1;
	vector = ft_calloc(1, sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->data = ft_calloc(elem, sizeof(void *));
	if (!vector->data)
	{
		free(vector);
		return (NULL);
	}
	vector->count = 0;
	vector->size = elem;
	return (vector);
}

void	expand_vector(t_vector *vector)
{
	void	**new;
	void	**old;
	int		i;

	i = 0;
	new = ft_calloc((vector->size * 2 + 1), sizeof(void *));
	if (!new)
		exit(1);
	old = vector->data;
	while (i < vector->count)
	{
		new[i] = vector->data[i];
		i++;
	}
	vector->data = new;
	vector->size *= 2;
	free(old);
}

void	add_elem(t_vector *vector, void *elem)
{
	if (!vector)
		return ;
	if (vector->count >= vector->size - 1)
		expand_vector(vector);
	vector->data[vector->count] = elem;
	vector->count++;
}

void	free_vector(t_vector *vector)
{
	int	i;

	if (!vector)
		return ;
	i = 0;
	while (i < vector->count)
	{
		if (vector->data[i])
		{
			free(vector->data[i]);
			vector->data[i] = NULL;
		}
		i++;
	}
	free(vector->data);
	vector->data = NULL;
	free(vector);
	vector = NULL;
}

void	free_split_vector(t_vector *vector)
{
	int		i;
	int		j;
	char	**arr;

	if (!vector)
		return ;
	i = 0;
	while (i < vector->count)
	{
		if (vector->data[i])
		{
			arr = (char **)vector->data[i];
			j = 0;
			while (arr[j])
				free(arr[j++]);
			free(arr);
			vector->data[i] = NULL;
		}
		i++;
	}
	free(vector->data);
	vector->data = NULL;
	free(vector);
}
