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

int game_loop(t_mlx *mlx)
{
  key_mouvment(mlx);
  key_rotation(mlx);
  ray_casting(mlx, mlx->data);
  mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.mlx_image, 0, 0);
  return (0);
}

t_img load_texture(t_mlx *mlx, char *path)
{
  t_img texture;

  texture.mlx_image = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width, &texture.height);
  if (!texture.mlx_image)
  {
    printf("failed to load %s\n",path);
    exit (1);
  }
  texture.image_data = mlx_get_data_addr(texture.mlx_image, &texture.bits_per_pixel, &texture.size_line, &texture.endian);
  return (texture);
}

void get_texture(t_mlx *mlx, t_data *data)
{
  data->tex_no = load_texture(mlx, data->no);
  data->tex_so = load_texture(mlx, data->so);
  data->tex_ea = load_texture(mlx, data->ea);
  data->tex_we = load_texture(mlx, data->we);
}

int main(int argc, char **argv)
{
  t_mlx mlx;
  t_pl player;
  t_data data;
  int i;

  if (argc == 2)
  {
    mlx.data = &data;
    mlx.player = &player;
    data.player = &player;
    data.mlx = &mlx;
    i = -1;
    while (++i < 6)
      data.key_pressed[i] = 0;
    if (parse(argv[1], &data))
      return(free_map(&data), 1);
    mlx.mlx = mlx_init();
    if(!mlx.mlx)
      return(clean_all(&mlx), 1);
    mlx.win = mlx_new_window(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba");
    if(!mlx.win)
      return(clean_all(&mlx), 1);
    get_texture(&mlx, &data);
    mlx.img.mlx_image = mlx_new_image(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    mlx.img.image_data = mlx_get_data_addr(mlx.img.mlx_image, &mlx.img.bits_per_pixel, &mlx.img.size_line, &mlx.img.endian);
    mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
    mlx_hook(mlx.win, 3, 1L << 1, key_release, &data);
    mlx_hook(mlx.win, 17, 0, red_cross, &mlx);
    mlx_loop_hook(mlx.mlx, game_loop, &mlx);
    mlx_loop(mlx.mlx);
    return (0);
  }
  printf("Error\n");
  return(1);
}

// int draw_wall_slice(t_mlx *mlx, double distance, int i, t_img *texture, double angle, double wall_x)
// {
//   int top;
//   int bottom;
//   int y;
//   double wall_h;
//   double center_x;
//   double center_y;
//   double radius;
//   int tex_x;
//   int tex_y;
//   int color;
//
//   center_x = OFFSET + mlx->data->pixel_size * 4;
//   center_y = OFFSET + mlx->data->pixel_size * 4;
//   radius = mlx->data->pixel_size * 4;
//   wall_h = SCREEN_HEIGHT / (distance * cos(angle));
//   top = (SCREEN_HEIGHT / 2) - (int)(wall_h / 2);
//   if (top < 0)
//     top = 0;
//   bottom = (SCREEN_HEIGHT / 2) + (int)(wall_h / 2);
//   if (bottom >= SCREEN_HEIGHT)
//     bottom = SCREEN_HEIGHT - 1;
//   tex_x = (int)(wall_x * texture->width);
//   y = top - 1;
//   while (++y <= bottom)
//   {
//     if (sqrt(pow(i - center_x, 2) + pow(y - center_y, 2)) > radius)
//     {
//       tex_y = (int)(((y - top) / wall_h) * texture->height);
//       color = get_texture_pixel(texture, tex_x, tex_y);
//       put_pixel_to_image(mlx->img, i, y, color);
//     }
//     else
//       y++;
//   }
//   y = -1;
//   while (++y < top)
//   {
//     if (sqrt(pow(i - center_x, 2) + pow(y - center_y, 2)) > radius)
//       put_pixel_to_image(mlx->img, i, y, 0x4ff2f7);
//   }
//   y = bottom;
//   while (++y < SCREEN_HEIGHT)
//     put_pixel_to_image(mlx->img, i, y, 0xf0a64d);
//   return (0);
// }
