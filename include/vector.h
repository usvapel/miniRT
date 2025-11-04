#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct s_vector {
  int count;
  int size;
  bool owns_data;
  void **data;
} t_vector;

t_vector *new_vector(size_t elem);
void add_elem(t_vector *vector, void *elem);
void free_vector(t_vector *vector);
void free_split_vector(t_vector *vector);

#endif // VECTOR_H
