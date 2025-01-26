#include <cub3D.h>

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

int get_tex_x(t_draw_map *d, t_img *texture)
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

void init_wall_slice(t_draw_wall_slice *w, t_draw_map *d, t_img *texture)
{
  d->wall_h = SCREEN_HEIGHT / d->wall_dist;
  w->top = (SCREEN_HEIGHT / 2) - (d->wall_h / 2);
  w->bottom = (SCREEN_HEIGHT / 2) + (d->wall_h / 2);
  if (w->top < 0)
    w->top = 0;
  if (w->bottom >= SCREEN_HEIGHT)
    w->bottom = SCREEN_HEIGHT - 1;
  w->tex_x = get_tex_x(d, texture);
  if (w->tex_x >= texture->width)
        w->tex_x = texture->width - 1;
  w->step = (double)texture->height / d->wall_h;
  w->tex_y = (w->top - SCREEN_HEIGHT / 2 + d->wall_h / 2) * w->step;
}

void draw_wall_slice(t_mlx *mlx, t_draw_map *d, t_img *texture, int column)
{
  t_draw_wall_slice w;

  init_wall_slice(&w, d, texture);
  w.y = -1;
  while (++w.y < w.top)
    put_pixel_to_image(mlx->img, column, w.y, 0x4ff2f7);
  while (w.y <= w.bottom)
  {
    if (w.y >= 0 && w.y < SCREEN_HEIGHT)
    {
      w.tex_y_int = (int)w.tex_y % texture->height;
      w.color = get_texture_pixel(texture, w.tex_x, w.tex_y_int);
      put_pixel_to_image(mlx->img, column, w.y++, w.color);
    }
    w.tex_y += w.step;
  }
  while (++w.y < SCREEN_HEIGHT)
    put_pixel_to_image(mlx->img, column, w.y, 0xf0a64d);
}

void init_ray_data_2(t_draw_map *d)
{
  if (d->ray_x < 0) 
    d->side_dist_x = (d->p_x - d->map_x) * d->dist_x;
  else  
    d->side_dist_x = (d->map_x + 1 - d->p_x) * d->dist_x;
  if (d->ray_y < 0) 
    d->side_dist_y = (d->p_y - d->map_y) * d->dist_y;
  else  
    d->side_dist_y = (d->map_y + 1 - d->p_y) * d->dist_y;
}

void init_ray_data(t_draw_map *d, t_data *data)
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
  init_ray_data_2(d);
}

void get_wall_dist(t_draw_map *d, t_data *data)
{
  d->side = 0;
  while (1)
  {
    if (d->side_dist_x < d->side_dist_y)
    {
      d->side_dist_x += d->dist_x;
      d->map_x += d->step_x;
      d->side = 0;
    }
    else
  {
      d->side_dist_y += d->dist_y;
      d->map_y += d->step_y;
      d->side = 1;
    }
    if (data->map[d->map_y][d->map_x] == '1')
      break;
  }
  if (d->side == 0)
    d->wall_dist = (d->map_x - d->p_x + (1 - d->step_x) / 2) / d->ray_x;
  else
    d->wall_dist = (d->map_y - d->p_y + (1 - d->step_y) / 2) / d->ray_y;
  d->wall_dist *= cos(data->player->angle - d->ray_angle);
}

/*---draw the 3D map (ray casting)---*/
void draw_map(t_mlx *mlx, t_data *data)
{
  t_draw_map d;

  d.start_angle = data->player->angle - FOV / 2;
  d.angle_step = FOV / NUM_RAYS;
  d.i = -1;
  while (++d.i < NUM_RAYS)
  {
    init_ray_data(&d, data);
    get_wall_dist(&d, data);
    if (d.side == 0)
    {
      if (d.step_x > 0)
        draw_wall_slice(mlx, &d, &data->tex_ea, d.i);
      else
        draw_wall_slice(mlx, &d, &data->tex_we, d.i);
    }
    else
  {
      if (d.step_y > 0)
        draw_wall_slice(mlx, &d, &data->tex_so, d.i);
      else
        draw_wall_slice(mlx, &d, &data->tex_no, d.i);
    }
  }
}
