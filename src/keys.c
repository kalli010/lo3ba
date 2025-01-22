#include <cub3D.h>

/*---change the input based on the player derection---*/
void get_direction_vector(float angle, float *dx, float *dy)
{
  *dx = cos(angle);
  *dy = sin(angle);
}

/*---remplace the player position---*/
int redraw_map(t_mlx *mlx, t_data *data, float new_x, float new_y)
{
  int x;
  int y;

  y = -1;

  while(data->map[++y])
  {
    x = -1;
    while(data->map[y][++x])
    {
      if(data->map[y][x] == 'P')
      {
        if(data->map[(int)new_y][(int)new_x] != '1');
        {
          data->map[y][x] = '0';
          data->map[(int)new_y][(int)new_x] = 'P';
          mlx->player->x = new_x;
          mlx->player->y = new_y;
          return (ray_casting(mlx, mlx->data, mlx->player), 0);
        }
      }
    }
  }
  return (0);
}

int collision_detection(t_mlx *mlx, float *new_x, float *new_y)
{
  t_data *data;

  // printf("ana hna\n");
  printf("n_x = %f , n_y = %f\n",*new_x, *new_y);
  // printf("ana hna\n");
  data = mlx->data;
  if (*new_x < 0 || *new_y < 0 || data->map[(int)*new_y] == NULL \
    || data->map[(int)*new_y][(int)*new_x] == '\0')
    return 0;
  if(data->map[(int)*new_y][(int)*new_x] == '1')
  {
    if (data->map[(int)*new_y][(int)mlx->player->x] == '1')
      *new_y = mlx->player->y;
    if (data->map[(int)mlx->player->y][(int)*new_x] == '1')
      *new_x = mlx->player->x;
  }
  return (redraw_map(mlx, data, *new_x, *new_y));
}

// /*---w,s,d,a keys---*/
int key_mouvment(int keycode, t_mlx *mlx)
{
  float dx;
  float dy;
  float move_speed;
  float new_x;
  float new_y;
  float temp;
  
  dx = 0;
  dy = 0;
  move_speed = 0.1;
  get_direction_vector(mlx->player->angle, &dx, &dy);
  if (keycode == 'w')
  {
  }
  else if (keycode == 's')
  {
    dx = -dx;
    dy = -dy;
  }
  else if (keycode == 'a')
  {
    temp = dx;
    dx = dy;
    dy = -temp;
  }
  else if (keycode == 'd')
  {
    temp = dx;
    dx = -dy;
    dy = temp;
  }
  new_x = mlx->player->x + dx * move_speed;
  new_y = mlx->player->y + dy * move_speed;
  printf("nn_x = %f , nn_y = %f\n", new_x,new_y);
  collision_detection(mlx, &new_x, &new_y);
  return (0);
}

/*---arrows keys---*/
int key_rotation(int keycode, t_mlx *mlx)
{
  float rotation_speed;

  rotation_speed = 0.05;
  if (keycode == 65361)
    mlx->player->angle -= rotation_speed;
  else if (keycode == 65363) 
    mlx->player->angle += rotation_speed;
  if (mlx->player->angle < 0)
    mlx->player->angle += 2 * M_PI;
  if (mlx->player->angle >= 2 * M_PI)
    mlx->player->angle -= 2 * M_PI;
  ray_casting(mlx, mlx->data, mlx->player);
  return (0);
}

int keys(int keycode, t_mlx *mlx)
{
  if (keycode == 65307)
  {
    clean_all(mlx);
    exit(0);
  }
  if (keycode == 'w' || keycode == 'a' || keycode == 's' || keycode == 'd')
    key_mouvment(keycode, mlx);
  else if (keycode == 65361 || keycode == 65363)
    key_rotation(keycode, mlx);
  return 0;
}

/*---red cross---*/
int red_cross(int keycode, t_mlx *mlx)
{
  // printf("%p\n",mlx);
  // printf("%p",mlx->mlx);
  // clean_all(mlx);
  exit(0);
  return(0);
}
