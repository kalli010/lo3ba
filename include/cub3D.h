#ifndef CUB3D_H
# define CUB3D_H

#define SIZE 48

#include <libft.h>
#include <get_next_line_bonus.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct s_data
{
} t_data;

typedef struct s_mlx
{
  void *mlx;
  void *win;
  char **map;
} t_mlx;

int parse(char *file, t_mlx *mlx);

#endif
