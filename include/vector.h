
#include <stdlib.h>

typedef struct s_vector
{
	size_t count;
	size_t size;
	void **data;
}	t_vector;


t_vector	*new_vector(size_t elem);
void	add_elem(t_vector *vector, void *elem);
