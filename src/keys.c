#include <cub3D.h>

/*---change the input based on the player derection---*/
void get_direction_vector(double angle, double *dx, double *dy)
{
  *dx = cos(angle);
  *dy = sin(angle);
}

/*---remplace the player position---*/
int redraw_map(t_mlx *mlx, t_data *data, double new_x, double new_y)
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

int collision_detection(t_mlx *mlx, double *new_x, double *new_y)
{
  t_data *data;

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
    if (data->map[(int)mlx->player->y][(int)*new_x] != '1' && \
      data->map[(int)*new_y][(int)mlx->player->x] != '1' && \
    data->map[(int)*new_y][(int)*new_x] == '1')
    {
      *new_y = mlx->player->y;
      *new_x = mlx->player->x;
    }
  }
  return (redraw_map(mlx, data, *new_x, *new_y));
}

// /*---w,s,d,a keys---*/
int key_mouvment(t_mlx *mlx)
{
  double dx;
  double dy;
  double new_x;
  double new_y;
  double temp;

  dx = 0;
  dy = 0;
  get_direction_vector(mlx->player->angle, &dx, &dy);
  if (mlx->data->key_pressed[0])
  {
    new_x = mlx->player->x + dx * MOVE_SPEED;
    new_y = mlx->player->y + dy * MOVE_SPEED;
  }
  else if (mlx->data->key_pressed[1])
  {
    dx = -dx;
    dy = -dy;
    new_x = mlx->player->x + dx * MOVE_SPEED;
    new_y = mlx->player->y + dy * MOVE_SPEED;
  }
  else if (mlx->data->key_pressed[2])
  {
    temp = dx;
    dx = dy;
    dy = -temp;
    new_x = mlx->player->x + dx * MOVE_SPEED;
    new_y = mlx->player->y + dy * MOVE_SPEED;
  }
  else if (mlx->data->key_pressed[3])
  {
    temp = dx;
    dx = -dy;
    dy = temp;
    new_x = mlx->player->x + dx * MOVE_SPEED;
    new_y = mlx->player->y + dy * MOVE_SPEED;
  }
  collision_detection(mlx, &new_x, &new_y);
  return (0);
}

/*---arrows keys---*/
int key_rotation(t_mlx *mlx)
{
  if (mlx->data->key_pressed[4])
    mlx->player->angle -= ROTATION_SPEED;
  if (mlx->data->key_pressed[5])
    mlx->player->angle += ROTATION_SPEED;
  if (mlx->player->angle < 0)
    mlx->player->angle += 2 * M_PI;
  if (mlx->player->angle >= 2 * M_PI)
    mlx->player->angle -= 2 * M_PI;
  ray_casting(mlx, mlx->data, mlx->player);
  return (0);
}

int key_press(int keycode, t_data *data)
{
  if (keycode == 65307)
  {
    clean_all(data->mlx);
    exit(0);
  }
  if (keycode == 'w')
    data->key_pressed[0] = 1;
  if (keycode == 's')
    data->key_pressed[1] = 1;
  if (keycode == 'a')
    data->key_pressed[2] = 1;
  if (keycode == 'd')
    data->key_pressed[3] = 1;
  if (keycode == 65361)
    data->key_pressed[4] = 1;
  if (keycode == 65363)
    data->key_pressed[5] = 1;
  return (0);
}

int key_release(int keycode, t_data *data)
{
  if (keycode == 'w')
    data->key_pressed[0] = 0;
  if (keycode == 's')
    data->key_pressed[1] = 0;
  if (keycode == 'a')
    data->key_pressed[2] = 0;
  if (keycode == 'd')
    data->key_pressed[3] = 0;
  if (keycode == 65361)
    data->key_pressed[4] = 0;
  if (keycode == 65363)
    data->key_pressed[5] = 0;
  return (0);
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
