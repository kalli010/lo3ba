#include <cub3D.h>

void free_map(t_mlx *mlx)
{
  int i;

  i = -1;
  while(mlx->map && mlx->map[++i])
    free(mlx->map[i]);
  free(mlx->map);
}

void clean_all(t_mlx *mlx)
{
  free_map(mlx);
  mlx_destroy_window(mlx->mlx, mlx->win);
  mlx_destroy_display(mlx->mlx);
  free(mlx->mlx);
}

int main(int argc, char **argv)
{
  t_mlx mlx;

  if (argc == 2)
  {
    if (parse(argv[1], &mlx))
      return(free_map(&mlx), 1);
    mlx.mlx = mlx_init();
    if(!mlx.mlx)
      return(clean_all(&mlx), 1);
    mlx.win = mlx_new_window(mlx.mlx, 500, 500, "cub3D");
    if(!mlx.win)
      return(clean_all(&mlx), 1);
    mlx_loop(mlx.mlx);
    return (0);
  }
  printf("Error\n");
  return(1);
}
