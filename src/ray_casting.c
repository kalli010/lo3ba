#include <cub3D.h>

void put_pixel_to_image(t_img img, int x, int y, int color)
{
  int *pixel_data;
  
  if (y >= SCREEN_HEIGHT || y < 0 || x < 0 || x >= SCREEN_WIDTH)
    return ;
  pixel_data = (int *)img.image_data;
  pixel_data[y * (img.size_line / 4) + x] = color;
}

int draw_wall_slice(t_mlx *mlx, float distance, int i, int wall_color, double angle)
{
  int top;
  int bottom;
  float wall_h;
  int y;

  wall_h = SCREEN_HEIGHT / (distance * cos(angle));
  top = (SCREEN_HEIGHT / 2) - (int)(wall_h / 2);
  bottom = (SCREEN_HEIGHT / 2) + (int)(wall_h / 2);
  y = -1;
  while (++y < top)
    put_pixel_to_image(mlx->img, i, y, 0x4ff2f7);
  while (top <= bottom)
  {
    put_pixel_to_image(mlx->img, i, top, wall_color);
    top++;
  }
  while (++top <= SCREEN_HEIGHT)
    put_pixel_to_image(mlx->img, i, top, 0xf0a64d);
  return (0);
}

int init_ray_data(t_draw_map *d, t_data *data)
{
  d->p_x = data->player->x;
  d->p_y = data->player->y;
  d->ray_angle = d->start_angle + d->i * d->angle_step;
  d->ray_x = cos(d->ray_angle);
  d->ray_y = sin(d->ray_angle);
  d->dist_x = fabs(1 / d->ray_x);
  d->dist_y = fabs(1 / d->ray_y);
  d->map_x = (int)d->p_x;
  d->map_y = (int)d->p_y;
  if (d->ray_x < 0)
    d->step_x = -1;
  else
    d->step_x = 1;
  if (d->ray_y < 0)
    d->step_y = -1;
  else
    d->step_y = 1;
  if (d->ray_x < 0) 
    d->side_dist_x = (d->p_x - d->map_x) * d->dist_x;
  else  
    d->side_dist_x = (d->map_x + 1 - d->p_x) * d->dist_x;
  if (d->ray_y < 0) 
    d->side_dist_y = (d->p_y - d->map_y) * d->dist_y;
  else  
    d->side_dist_y = (d->map_y + 1 - d->p_y) * d->dist_y;
}

/*---draw the 3D map (ray casting)---*/
void draw_map(t_mlx *mlx, t_data *data)
{
  t_draw_map d;
  int side;
  float wall_dist;
  int wall_color;

  d.start_angle = data->player->angle - FOV / 2;
  d.angle_step = FOV / NUM_RAYS;
  d.i = -1;
  while (++d.i < NUM_RAYS)
  {
    init_ray_data(&d, data);
    side = 0;
    
    while (1)
    {
      // printf("side_dist (%f, %f), d.map (%f, %f)\n", d.side_dist_x, d.side_dist_y, d.map_x, d.map_y);
      if (d.side_dist_x < d.side_dist_y)
      {
        d.side_dist_x += d.dist_x;
        d.map_x += d.step_x;
        side = 0;
      }
      else
      {
        d.side_dist_y += d.dist_y;
        d.map_y += d.step_y;
        side = 1;
      }
      if (data->map[d.map_y][d.map_x] == '1')
        break ;
    }
    if (side == 0) 
      wall_dist = (d.map_x - d.p_x + (1 - d.step_x) / 2) / d.ray_x;
    else
      wall_dist = (d.map_y - d.p_y + (1 - d.step_y) / 2) / d.ray_y;
    if (side == 0)
    {
      if (d.step_x > 0)
        wall_color = 0xFF0000;
      else
        wall_color = 0x0000FF;
    }
    else
  {
      if (d.step_y > 0)
        wall_color = 0xFFFF00;
      else 
        wall_color = 0x00FF00;
    }
    draw_wall_slice(mlx, wall_dist, d.i, wall_color, mlx->player->angle - d.ray_angle);
  }
}

/*calculate the pixel size for the minimap*/
int calculate_pixel_size(t_data *data)
{
  int pixel_size_w;
  int pixel_size_h;
  int minimap_w;
  int minimap_h;
  int pixel_size;

  minimap_w = SCREEN_WIDTH * MINIMAP_SCALE;
  minimap_h = SCREEN_HEIGHT * MINIMAP_SCALE;
  pixel_size_w = minimap_w / data->map_w;
  pixel_size_h = minimap_h / data->map_h;
  return (fmin(pixel_size_w, pixel_size_h));
}

int pixel_put(t_mlx *mlx, float x, float y, int color)
{
  int i;
  int j;

  i = -1;
  while (++i < mlx->data->pixel_size)
  {
    j = -1;
    while (++j < mlx->data->pixel_size)
    {
      // if(i == 0 || i == mlx->data->pixel_size - 1 || j == 0 || j == mlx->data->pixel_size - 1)
      //   put_pixel_to_image(mlx->img, 10 + y * mlx->data->pixel_size + j, 10 + x * mlx->data->pixel_size + i, 0x32a852);
      // else
      put_pixel_to_image(mlx->img, 10 + y * mlx->data->pixel_size + j, 10 + x * mlx->data->pixel_size + i, color);
    }
  }
}

/*---Draw the minimap---*/
int draw_minimap(t_mlx *mlx, t_data *data)
{
  int x;
  int y;

  x = -1;
  while(data->map[++x])
  {
    y = -1;
    while(data->map[x][++y])
    {
      if (data->map[x][y] == '1') 
        pixel_put(mlx, x, y, 0x00000);
      else
        pixel_put(mlx, x, y, 0xf0a64d);
    }
  }
  // pixel_put(mlx, mlx->player->y, mlx->player->x, 0xffffff);
}

/*---Draw the rays---*/
void draw_rays(t_mlx *mlx, t_data *data)
{
  t_draw_rays d;

  d.ray_start_angle = data->player->angle - FOV / 2;
  d.ray_angle_step = FOV / NUM_RAYS; 
  d.i = -1;
  while(++d.i < NUM_RAYS)
  {
    d.ray_angle = d.ray_start_angle + d.i * d.ray_angle_step;
    d.ray_x = data->player->x;
    d.ray_y = data->player->y;
    d.step_x = cos(d.ray_angle);
    d.step_y = sin(d.ray_angle);
    while (1)
    {
      d.ray_x += d.step_x * 0.05;
      d.ray_y += d.step_y * 0.05;
      if (d.ray_x < 0 || d.ray_y < 0 || !data->map[(int)d.ray_y] \
        || data->map[(int)d.ray_y][(int)d.ray_x] == '1' \
        || data->map[(int)d.ray_y][(int)d.ray_x] == '\0')
        break;
      put_pixel_to_image(mlx->img, 10 + d.ray_x * data->pixel_size, 10 + d.ray_y * data->pixel_size, 0xFF0000);
    }
  }
}

/*---draw everything---*/
int ray_casting(t_mlx *mlx, t_data *data, t_pl *player)
{
  draw_map(mlx, mlx->data);
  data->pixel_size = calculate_pixel_size(data);
  draw_minimap(mlx, data);
  draw_rays(mlx, mlx->data);
  mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.mlx_image, 0, 0);
  return(0);
}
