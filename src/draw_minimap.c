/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:12:18 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:23:57 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*draw the minimap background*/
void	draw_circle(t_mlx *mlx)
{
	int	center_x;
	int	center_y;
	int	r;
	int	x;
	int	y;

	center_x = OFFSET + mlx->data->pixel_size * 4;
	center_y = OFFSET + mlx->data->pixel_size * 4;
	r = mlx->data->pixel_size * 4;
	y = center_y - r - 1;
	while (++y <= center_y + r)
	{
		x = center_x - r - 1;
		while (++x <= center_x + r)
		{
			if ((x - center_x) * (x - center_x) + (y - center_y) * (y
					- center_y) <= r * r)
				put_pixel_to_image(mlx->img, x, y, 0x000000);
		}
	}
}

void	pixel_put(t_mlx *mlx, double map_x, double map_y, int color)
{
	t_pixel_put	p;
	int			i;
	int			j;

	p.center_x = OFFSET + mlx->data->pixel_size * 4;
	p.center_y = OFFSET + mlx->data->pixel_size * 4;
	p.i_x = p.center_x + (map_x - mlx->player->x) * mlx->data->pixel_size;
	p.i_y = p.center_y + (map_y - mlx->player->y) * mlx->data->pixel_size;
	i = -1;
	while (++i < mlx->data->pixel_size)
	{
		j = -1;
		while (++j < mlx->data->pixel_size)
		{
			p.new_x = p.i_x + j;
			p.new_y = p.i_y + i;
			p.distance = (p.new_x - p.center_x) * (p.new_x - p.center_x)
				+ (p.new_y - p.center_y) * (p.new_y - p.center_y);
			if (p.distance <= (mlx->data->pixel_size * 4)
				* (mlx->data->pixel_size * 4))
				put_pixel_to_image(mlx->img, p.new_x, p.new_y, color);
		}
	}
}

/*---Draw the minimap---*/
void	draw_minimap(t_mlx *mlx, t_data *data)
{
	t_draw_minimap	d;

	d.start_x = (int)mlx->player->x - 4;
	d.start_y = (int)mlx->player->y - 4;
	d.end_x = (int)mlx->player->x + 4;
	d.end_y = (int)mlx->player->y + 4;
	d.y = d.start_y - 1;
	while (++d.y <= d.end_y)
	{
		d.x = d.start_x - 1;
		while (++d.x <= d.end_x)
		{
			if (d.y >= 0 && d.x >= 0 && d.y < data->map_h && d.x < data->map_w)
			{
				if (data->map[d.y][d.x] == '1')
					pixel_put(mlx, d.x, d.y, 0x000000);
				else if (data->map[d.y][d.x] == 'D')
					pixel_put(mlx, d.x, d.y, 0x521827);
				else if (data->map[d.y][d.x] == 'B')
					pixel_put(mlx, d.x, d.y, 0x194a15);
				else
					pixel_put(mlx, d.x, d.y, 0x908c96);
			}
		}
	}
}

/*---Draw the rays---*/
void	draw_rays(t_mlx *mlx, t_data *data)
{
	t_draw_rays	d;

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
			if (calculate_rays(mlx, data, &d))
				break ;
		}
	}
}
