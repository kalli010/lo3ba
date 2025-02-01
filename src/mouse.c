/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:58:49 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/31 19:59:19 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	mouse_rotation(int x, int y, t_data *data)
{
	unsigned long	current_time;

	(void)y;
	current_time = get_current_time();
	if (data->last_mouse_x == -1)
	{
		data->last_mouse_x = x;
		return (data->last_mouse_time = current_time, 0);
	}
	if (x != data->last_mouse_x)
	{
		data->mouse_moving = 1;
		data->last_mouse_time = current_time;
		if (x < data->last_mouse_x)
		{
			data->key_pressed[4] = 1;
			data->key_pressed[5] = 0;
		}
		else if (x > data->last_mouse_x)
		{
			data->key_pressed[5] = 1;
			data->key_pressed[4] = 0;
		}
	}
	return (data->last_mouse_x = x, 0);
}

int	mouse_click(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 3 && !data->spirit.animating)
	{
		data->spirit.animating = 1;
		data->spirit.current_frame = 0;
		data->key_pressed[6] = 1;
		data->spirit.last_frame = 0.0;
	}
	return (0);
}

void	wait_for_frame(t_data *data)
{
	unsigned long	current_time;
	double			frame_delay;

	current_time = get_current_time();
	frame_delay = 1000.0 / 30.00;
	if (current_time - data->spirit.last_frame < frame_delay)
		usleep((frame_delay - (current_time - data->spirit.last_frame)) * 1000);
}

void	check_frame(t_mlx *mlx)
{
	if (mlx->data->spirit.current_frame >= 21)
	{
		mlx->data->spirit.animating = 0;
		mlx->data->spirit.current_frame = 0;
		mlx->data->spirit.last_frame = 0.0;
		mlx->data->key_pressed[6] = 0;
	}
}

void	left_click(t_mlx *mlx)
{
	int	x;
	int	y;
	int	color;

	mlx->data->spirit.last_frame = get_current_time();
	if (mlx->data->key_pressed[6] && mlx->data->spirit.animating)
	{
		y = -1;
		while (++y < SCREEN_HEIGHT)
		{
			x = -1;
			while (++x < SCREEN_WIDTH)
			{
				color = get_texture_pixel(&mlx->data->spirit.\
						aim[mlx->data->spirit.current_frame],
						x, y);
				if (color != -16777216)
					put_pixel_to_image(mlx->img, x, y, color);
			}
		}
		mlx->data->spirit.current_frame++;
		check_frame(mlx);
	}
	wait_for_frame(mlx->data);
}
