/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:10:41 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:17:27 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	draw_wall_slice(t_mlx *mlx, t_draw_map *d, t_img *texture, int column)
{
	t_draw_wall_slice	w;

	init_wall_slice(&w, d, texture);
	w.y = -1;
	while (++w.y < w.top)
		put_pixel_to_image(mlx->img, column, w.y, mlx->data->c_value);
	while (w.y <= w.bottom)
	{
		if (w.y >= 0 && w.y < SCREEN_HEIGHT)
		{
			w.tex_y_int = (int)w.tex_y % texture->height;
			w.color = get_texture_pixel(texture, w.tex_x, w.tex_y_int);
			if (w.color != -16777216)
				put_pixel_to_image(mlx->img, column, w.y, w.color);
			w.y++;
		}
		w.tex_y += w.step;
	}
	while (++w.y < SCREEN_HEIGHT)
		put_pixel_to_image(mlx->img, column, w.y, mlx->data->f_value);
}

void	init_ray_data(t_draw_map *d, t_data *data)
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

void	get_wall_dist(t_draw_map *d, t_data *data)
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
		if (data->mini_map[d->map_y][d->map_x] == '1'
			|| data->mini_map[d->map_y][d->map_x] == 'D')
			break ;
	}
	if (d->side == 0)
		d->wall_dist = (d->map_x - d->p_x + (1 - d->step_x) / 2) / d->ray_x;
	else
		d->wall_dist = (d->map_y - d->p_y + (1 - d->step_y) / 2) / d->ray_y;
	d->wall_dist *= cos(data->player->angle - d->ray_angle);
}

void	draw_wall(t_mlx *mlx, t_data *data, t_draw_map *d)
{
	if (d->side == 0)
	{
		if (d->step_x > 0)
			draw_wall_slice(mlx, d, &data->tex_ea, d->i);
		else
			draw_wall_slice(mlx, d, &data->tex_we, d->i);
	}
	else
	{
		if (d->step_y > 0)
			draw_wall_slice(mlx, d, &data->tex_so, d->i);
		else
			draw_wall_slice(mlx, d, &data->tex_no, d->i);
	}
}

/*---draw the 3D map (ray casting)---*/
void	draw_map(t_mlx *mlx, t_data *data)
{
	t_draw_map	d;

	d.start_angle = data->player->angle - FOV / 2;
	d.angle_step = FOV / NUM_RAYS;
	d.i = -1;
	while (++d.i < NUM_RAYS)
	{
		init_ray_data(&d, data);
		get_wall_dist(&d, data);
		if (data->mini_map[d.map_y][d.map_x] == 'D')
			draw_wall_slice(mlx, &d, &data->door, d.i);
		else
			draw_wall(mlx, data, &d);
	}
}
