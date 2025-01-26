/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:21:32 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:21:35 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*calculate the pixel size for the minimap*/
int	calculate_pixel_size(void)
{
	int	pixel_size_w;
	int	pixel_size_h;
	int	minimap_w;
	int	minimap_h;

	minimap_w = SCREEN_WIDTH * MINIMAP_SCALE;
	minimap_h = SCREEN_HEIGHT * MINIMAP_SCALE;
	pixel_size_w = minimap_w / 16;
	pixel_size_h = minimap_h / 15;
	return (fmin(pixel_size_w, pixel_size_h));
}

int	calculate_rays(t_mlx *mlx, t_data *data, t_draw_rays *d)
{
	double	new_x;
	double	new_y;

	d->ray_x += d->step_x * 0.05;
	d->ray_y += d->step_y * 0.05;
	if (d->ray_x < 0 || d->ray_y < 0 || !data->map[(int)d->ray_y]
		|| data->map[(int)d->ray_y][(int)d->ray_x] == '1')
		return (1);
	new_x = (d->ray_x - data->player->x) * data->pixel_size;
	new_y = (d->ray_y - data->player->y) * data->pixel_size;
	if (sqrt(new_x * new_x + new_y * new_y) > mlx->data->pixel_size * 4)
		return (1);
	put_pixel_to_image(mlx->img, new_x + OFFSET + mlx->data->pixel_size * 4,
		new_y + OFFSET + mlx->data->pixel_size * 4, 0xFFFFFF);
	return (0);
}
