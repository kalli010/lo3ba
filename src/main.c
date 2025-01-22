#include <cub3D.h>

void free_map(t_data *data)
{
  int i;

  i = 0;
  while(data->map && data->map[i])
  {
    free(data->map[i]);
    i++;
  }
  free(data->map);
}

void clean_all(t_mlx *mlx)
{
  mlx_destroy_window(mlx->mlx, mlx->win);
  mlx_destroy_display(mlx->mlx);
  free_map(mlx->data);
  free(mlx->mlx);
}

int main(int argc, char **argv)
{
  t_mlx mlx;
  t_pl player;
  t_data data;

  if (argc == 2)
  {
    mlx.data = &data;
    mlx.player = &player;
    data.player = &player;
    if (parse(argv[1], &data, &player))
      return(free_map(&data), 1);
    mlx.mlx = mlx_init();
    if(!mlx.mlx)
      return(clean_all(&mlx), 1);
    mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba");
    if(!mlx.win)
      return(clean_all(&mlx), 1);
    mlx.img.mlx_image = mlx_new_image(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx.img.image_data = mlx_get_data_addr(mlx.img.mlx_image, &mlx.img.bits_per_pixel, &mlx.img.size_line, &mlx.img.endian);
    ray_casting(&mlx, &data, &player);
    mlx_hook(mlx.win, 2, 1, keys, &mlx);
    mlx_hook(mlx.win, 17, 0, red_cross, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
  }
  printf("Error\n");
  return(1);
}
