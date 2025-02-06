/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:23:20 by zelkalai          #+#    #+#             */
/*   Updated: 2025/02/06 09:51:33 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

unsigned long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*---change the input based on the player derection---*/
void	get_direction_vector(double angle, double *dx, double *dy)
{
	*dx = cos(angle);
	*dy = sin(angle);
}

int	check_corner(t_data *data, t_mlx *mlx, double new_x, double new_y)
{
	return ((data->mini_map[(int)mlx->player->y][(int)new_x] != '1' \
				&& data->mini_map[(int)new_y][(int)mlx->player->x] != '1' \
				&& data->mini_map[(int)new_y][(int)new_x] == '1') \
			|| (data->mini_map[(int)mlx->player->y][(int)new_x] != 'D' \
				&& data->mini_map[(int)new_y][(int)mlx->player->x] != 'D' \
				&& data->mini_map[(int)new_y][(int)new_x] == 'D'));
}

void	collision_detection(t_mlx *mlx, double *new_x, double *new_y)
{
	t_data	*data;

	data = mlx->data;
	if (*new_x < 0 || *new_y < 0 || data->mini_map[(int)*new_y] == NULL
		|| data->mini_map[(int)*new_y][(int)*new_x] == '\0')
		return ;
	if (data->mini_map[(int)*new_y][(int)*new_x] == '1'
		|| data->mini_map[(int)*new_y][(int)*new_x] == 'D')
	{
		if (data->mini_map[(int)*new_y][(int)mlx->player->x] == '1'
			|| data->mini_map[(int)*new_y][(int)mlx->player->x] == 'D')
			*new_y = mlx->player->y;
		if (data->mini_map[(int)mlx->player->y][(int)*new_x] == '1'
			|| data->mini_map[(int)mlx->player->y][(int)*new_x] == 'D')
			*new_x = mlx->player->x;
		if (check_corner(data, mlx, *new_x, *new_y))
		{
			*new_y = mlx->player->y;
			*new_x = mlx->player->x;
		}
	}
	mlx->player->x = *new_x;
	mlx->player->y = *new_y;
}

void	change_x_y(t_mlx *mlx, t_key_mouvment *k)
{
	k->new_x = mlx->player->x + k->dx * MOVE_SPEED;
	k->new_y = mlx->player->y + k->dy * MOVE_SPEED;
	if ((mlx->data->mini_map[(int)mlx->player->y][(int)k->new_x] == '1' \
				|| mlx->data->mini_map[(int)mlx->\
				player->y][(int)k->new_x] == 'D') \
			&& (mlx->data->mini_map[(int)k->new_y][(int)mlx->player->x] == '1' \
			|| mlx->data->mini_map[(int)k->new_y][(int)mlx->player->x] == 'D') \
		&& (mlx->data->mini_map[(int)k->new_y][(int)k->new_x] != '1' \
			|| mlx->data->mini_map[(int)k->new_y][(int)k->new_x] != 'D'))
	{
		k->new_y = mlx->player->y;
		k->new_x = mlx->player->x;
	}
	collision_detection(mlx, &k->new_x, &k->new_y);
}
