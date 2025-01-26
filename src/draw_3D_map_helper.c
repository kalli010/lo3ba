/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D_map_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:17:06 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:18:14 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	put_pixel_to_image(t_img img, int x, int y, int color)
{
	int	*pixel_data;

	if (y >= SCREEN_HEIGHT || y < 0 || x < 0 || x >= SCREEN_WIDTH)
		return ;
	if (!img.image_data)
		return ;
	pixel_data = (int *)img.image_data;
	pixel_data[y * (img.size_line / 4) + x] = color;
}

int	get_tex_x(t_draw_map *d, t_img *texture)
{
	double	wall_x;

	if (d->side == 0)
		wall_x = d->p_y + d->wall_dist * d->ray_y;
	else
		wall_x = d->p_x + d->wall_dist * d->ray_x;
	wall_x -= floor(wall_x);
	return ((int)(wall_x * texture->width));
}

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->image_data + (y * texture->size_line + x
			* (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	init_wall_slice(t_draw_wall_slice *w, t_draw_map *d, t_img *texture)
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
