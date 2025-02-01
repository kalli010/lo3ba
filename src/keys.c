/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:10:26 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:22:39 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	check_door(t_data *data)
{
	t_pl	*pl;

	pl = data->player;
	if (data->map[(int)(pl->y + sin(pl->angle))][(int)(pl->x
			+ cos(pl->angle))] == 'D')
	{
		if (data->map[(int)pl->y][(int)pl->x] != 'D')
			data->map[(int)(pl->y + sin(pl->angle))][(int)(pl->x
					+ cos(pl->angle))] = 'B';
	}
	else if (data->map[(int)(pl->y + sin(pl->angle))][(int)(pl->x
			+ cos(pl->angle))] == 'B')
	{
		if (data->map[(int)pl->y][(int)pl->x] != 'B')
			data->map[(int)(pl->y + sin(pl->angle))][(int)(pl->x
					+ cos(pl->angle))] = 'D';
	}
}

/*---w,s,d,a keys---*/
void	key_mouvment(t_mlx *mlx)
{
	t_key_mouvment	k;

	get_direction_vector(mlx->player->angle, &k.dx, &k.dy);
	if (mlx->data->key_pressed[0])
		change_x_y(mlx, &k);
	else if (mlx->data->key_pressed[1])
	{
		k.dx = -k.dx;
		k.dy = -k.dy;
		change_x_y(mlx, &k);
	}
	else if (mlx->data->key_pressed[2])
	{
		k.temp = k.dx;
		k.dx = k.dy;
		k.dy = -k.temp;
		change_x_y(mlx, &k);
	}
	else if (mlx->data->key_pressed[3])
	{
		k.temp = k.dx;
		k.dx = -k.dy;
		k.dy = k.temp;
		change_x_y(mlx, &k);
	}
}

/*---arrows keys---*/
int	key_rotation(t_mlx *mlx)
{
	if (mlx->data->key_pressed[4])
		mlx->player->angle -= ROTATION_SPEED;
	if (mlx->data->key_pressed[5])
		mlx->player->angle += ROTATION_SPEED;
	if (mlx->player->angle < 0)
		mlx->player->angle += 2 * M_PI;
	if (mlx->player->angle >= 2 * M_PI)
		mlx->player->angle -= 2 * M_PI;
	return (0);
}

int	key_press(int keycode, t_data *data)
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
	if (keycode == 'q')
		check_door(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
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
