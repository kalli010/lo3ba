/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:23:20 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:23:21 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

/*---change the input based on the player derection---*/
void	get_direction_vector(double angle, double *dx, double *dy)
{
	*dx = cos(angle);
	*dy = sin(angle);
}

void	collision_detection(t_mlx *mlx, double *new_x, double *new_y)
{
	t_data	*data;

	data = mlx->data;
	if (*new_x < 0 || *new_y < 0 || data->map[(int)*new_y] == NULL
		|| data->map[(int)*new_y][(int)*new_x] == '\0')
		return ;
	if (data->map[(int)*new_y][(int)*new_x] == '1')
	{
		if (data->map[(int)*new_y][(int)mlx->player->x] == '1')
			*new_y = mlx->player->y;
		if (data->map[(int)mlx->player->y][(int)*new_x] == '1')
			*new_x = mlx->player->x;
		if (data->map[(int)mlx->player->y][(int)*new_x] != '1'
			&& data->map[(int)*new_y][(int)mlx->player->x] != '1'
			&& data->map[(int)*new_y][(int)*new_x] == '1')
		{
			*new_y = mlx->player->y;
			*new_x = mlx->player->x;
		}
	}
	mlx->player->x = *new_x;
	mlx->player->y = *new_y;
	ray_casting(mlx, mlx->data);
}

void	change_x_y(t_mlx *mlx, t_key_mouvment *k)
{
	k->new_x = mlx->player->x + k->dx * MOVE_SPEED;
	k->new_y = mlx->player->y + k->dy * MOVE_SPEED;
	if (mlx->data->map[(int)mlx->player->y][(int)k->new_x] == '1'
		&& mlx->data->map[(int)k->new_y][(int)mlx->player->x] == '1'
		&& mlx->data->map[(int)k->new_y][(int)k->new_x] != '1')
	{
		k->new_y = mlx->player->y;
		k->new_x = mlx->player->x;
	}
	collision_detection(mlx, &k->new_x, &k->new_y);
}
