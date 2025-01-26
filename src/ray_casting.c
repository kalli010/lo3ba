#include <cub3D.h>

int get_tex_x(t_data *data, t_draw_map *d, t_img *texture)
{
    double wall_x;

    if (d->side == 0)
        wall_x = d->p_y + d->wall_dist * d->ray_y;
    else
        wall_x = d->p_x + d->wall_dist * d->ray_x;
    wall_x -= floor(wall_x);
    return ((int)(wall_x * texture->width));
}

int get_texture_pixel(t_img *texture, int x, int y)
{
  char *pixel;

  if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
    return (0);
  pixel = texture->image_data + (y * texture->size_line + x * (texture->bits_per_pixel / 8));
  return (*(int *)pixel);
}

void put_pixel_to_image(t_img img, int x, int y, int color)
{
    int *pixel_data;

    if (y >= SCREEN_HEIGHT || y < 0 || x < 0 || x >= SCREEN_WIDTH)
        return;
    if (!img.image_data)
        return;
    pixel_data = (int *)img.image_data;
    pixel_data[y * (img.size_line / 4) + x] = color;
}

void draw_wall_slice(t_mlx *mlx, t_draw_map *d, t_img *texture, int column)
{
  int top; 
  int bottom;
  double tex_y; 
  double step;
  int tex_x; 
  int tex_y_int; 
  int color;
  int y;

  d->wall_h = SCREEN_HEIGHT / d->wall_dist;
  top = (SCREEN_HEIGHT / 2) - (d->wall_h / 2);
  bottom = (SCREEN_HEIGHT / 2) + (d->wall_h / 2);
  if (top < 0)
    top = 0;
  if (bottom >= SCREEN_HEIGHT)
    bottom = SCREEN_HEIGHT - 1;
  tex_x = get_tex_x(mlx->data, d, texture);
  if (tex_x >= texture->width)
        tex_x = texture->width - 1;
  step = (double)texture->height / d->wall_h;
  tex_y = (top - SCREEN_HEIGHT / 2 + d->wall_h / 2) * step;
  y = top - 1;
  while (++y <= bottom)
  {
    if (y >= 0 && y < SCREEN_HEIGHT)
    {
      tex_y_int = (int)tex_y % texture->height;
      color = get_texture_pixel(texture, tex_x, tex_y_int);
      put_pixel_to_image(mlx->img, column, y, color);
    }
    tex_y += step;
  }
  y = -1;
  while (++y < top)
    put_pixel_to_image(mlx->img, column, y, 0x4ff2f7);
  y = bottom;
  while (++y < SCREEN_HEIGHT)
    put_pixel_to_image(mlx->img, column, y, 0xf0a64d);
}

int init_ray_data(t_draw_map *d, t_data *data)
{
  d->p_x = data->player->x;
  d->p_y = data->player->y;
  d->ray_angle = d->start_angle + d->i * d->angle_step;
  d->ray_x = cos(d->ray_angle);
  d->ray_y = sin(d->ray_angle);
  if (d->ray_x == 0)
    d->dist_x = INFINITY;
  else
    d->dist_x = fabs(1 / d->ray_x);
  if (d->ray_y == 0)
    d->dist_y = INFINITY;
  else
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
  return(0);
}

/*---draw the 3D map (ray casting)---*/
void draw_map(t_mlx *mlx, t_data *data)
{
  t_draw_map d;
  t_img *texture;

  d.start_angle = data->player->angle - FOV / 2;
  d.angle_step = FOV / NUM_RAYS;
  d.i = -1;
  while (++d.i < NUM_RAYS)
  {
    if (init_ray_data(&d, data))
      return;

    d.side = 0;
    while (1)
    {
      if (d.side_dist_x < d.side_dist_y)
      {
        d.side_dist_x += d.dist_x;
        d.map_x += d.step_x;
        d.side = 0;
      }
      else
    {
        d.side_dist_y += d.dist_y;
        d.map_y += d.step_y;
        d.side = 1;
      }
      if (data->map[d.map_y][d.map_x] == '1')
        break;
    }
    if (d.side == 0)
      d.wall_dist = (d.map_x - d.p_x + (1 - d.step_x) / 2) / d.ray_x;
    else
      d.wall_dist = (d.map_y - d.p_y + (1 - d.step_y) / 2) / d.ray_y;
    d.wall_dist *= cos(data->player->angle - d.ray_angle);
    if (d.side == 0)
    {
      if (d.step_x > 0)
        texture = &data->tex_ea;
      else
        texture = &data->tex_we;
    }
    else
    {
      if (d.step_y > 0)
        texture = &data->tex_so;
      else
        texture = &data->tex_no;
    }
    draw_wall_slice(mlx, &d, texture, d.i);
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
  pixel_size_w = minimap_w / 16;
  pixel_size_h = minimap_h / 15;
  return (fmin(pixel_size_w, pixel_size_h));
}

/*draw the minimap background*/
void draw_circle(t_mlx *mlx)
{
  int center_x;
  int center_y;
  int r;
  int x;
  int y;

  center_x = OFFSET + mlx->data->pixel_size * 4;
  center_y = OFFSET + mlx->data->pixel_size * 4;
  r = mlx->data->pixel_size * 4;
  y = center_y - r - 1;
  while (++y <= center_y + r)
  {
    x = center_x - r - 1;
    while (++x <= center_x + r)
    {
      if ((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y) <= r * r)
        put_pixel_to_image(mlx->img, x, y, 0x000000);
    }
  }
}

int pixel_put(t_mlx *mlx, double map_x, double map_y, int color)
{
  int i, j;
  int center_x;
  int center_y;
  double new_x;
  double new_y;
  double distance;
  double i_x;
  double i_y;

  center_x = OFFSET + mlx->data->pixel_size * 4;
  center_y = OFFSET + mlx->data->pixel_size * 4;
  i_x = center_x + (map_x - mlx->player->x) * mlx->data->pixel_size;
  i_y = center_y + (map_y - mlx->player->y) * mlx->data->pixel_size;
  i = -1;
  while (++i < mlx->data->pixel_size)
  {
    j = -1;
    while (++j < mlx->data->pixel_size)
    {
      new_x = i_x + j;
      new_y = i_y + i;
      distance = (new_x - center_x) * (new_x - center_x) + \
        (new_y - center_y) * (new_y - center_y);
      if (distance <= (mlx->data->pixel_size * 4) * (mlx->data->pixel_size * 4))
        put_pixel_to_image(mlx->img, new_x, new_y, color);
    }
  }
  return (0);
}

/*---Draw the minimap---*/
int draw_minimap(t_mlx *mlx, t_data *data)
{
  int x;
  int y;
  int start_x;
  int start_y;
  int end_x;
  int end_y;

  start_x = (int)mlx->player->x - 5;
  start_y = (int)mlx->player->y - 5;
  end_x = (int)mlx->player->x + 5;
  end_y = (int)mlx->player->y + 5;
  y = start_y - 1;
  while (++y <= end_y)
  {
    x = start_x - 1;
    while (++x <= end_x)
    {
      if (y >= 0 && x >= 0 && y < data->map_h && x < data->map_w)
      {
        if (data->map[y][x] == '1')
          pixel_put(mlx, x, y, 0x000000);
        else
          pixel_put(mlx, x, y, 0x908c96);
      }
    }
  }
  return (0);
}

/*---Draw the rays---*/
void draw_rays(t_mlx *mlx, t_data *data)
{
  t_draw_rays d;
  double new_x; 
  double new_y;

  d.ray_start_angle = data->player->angle - FOV / 2;
  d.ray_angle_step = FOV / NUM_RAYS;
  d.i = -1;
  while (++d.i < NUM_RAYS)
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
      if (d.ray_x < 0 || d.ray_y < 0 || !data->map[(int)d.ray_y] || data->map[(int)d.ray_y][(int)d.ray_x] == '1')
        break;
      new_x = (d.ray_x - data->player->x) * data->pixel_size;
      new_y = (d.ray_y - data->player->y) * data->pixel_size;
      if (sqrt(new_x * new_x + new_y * new_y) > mlx->data->pixel_size * 4)
        break;
      put_pixel_to_image(mlx->img, new_x + OFFSET + mlx->data->pixel_size * 4,
                         new_y + OFFSET + mlx->data->pixel_size * 4, 0xFFFFFF);
    }
  }
}

/*---draw everything---*/
int ray_casting(t_mlx *mlx, t_data *data, t_pl *player)
{
  draw_map(mlx, mlx->data);
  data->pixel_size = calculate_pixel_size(data);
  draw_circle(mlx);
  draw_minimap(mlx, data);
  draw_rays(mlx, mlx->data);
  return(0);
}
