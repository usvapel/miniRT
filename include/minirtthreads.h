#ifndef MINIRT_THREADS_H
#define MINIRT_THREADS_H

#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdint.h>

// Forward declaration to avoid including MLX42.h
typedef struct mlx_image mlx_image_t;

typedef struct s_threads {
  pthread_t thread;
  int index;
  int start_y;
  int end_y;
  int start_x;
  int end_x;
  atomic_bool done;
  atomic_bool end;
  atomic_int block_size;
  bool last_move;
  int depth;
  int y;
  mlx_image_t *target_buffer;
} t_threads;

#endif // MINIRT_THREADS_H
