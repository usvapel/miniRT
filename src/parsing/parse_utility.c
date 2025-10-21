#include "minirt.h"

void	runtime_error(char *s)
{
	printf("Error\n");
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}

void	free_array(void **array)
{
	void	**copy;

	if (!array)
		return ;
	copy = array;
	while (*copy)
		free(*copy++);
	free(array);
}

void	free_values(char **values[3], int count)
{
	int	i;

	i = 0;
	while (i < count)
		free_array((void *)values[i++]);
}

char	**safe_split(char **values[3], int count, char *line)
{
	char	**splitted;

	if (!line)
		runtime_error("Possible invalid/missing values!");
	splitted = ft_split(line, ',');
	if (!splitted)
	{
		free_values(values, count);
		runtime_error("failure during memory allocation!");
	}
	return (splitted);
}

