/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:25:38 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:25:39 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map && data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

void	clean_all(t_mlx *mlx)
{
	int	i;

	mlx_destroy_image(mlx->mlx, mlx->data->tex_no.mlx_image);
	mlx_destroy_image(mlx->mlx, mlx->data->tex_so.mlx_image);
	mlx_destroy_image(mlx->mlx, mlx->data->tex_we.mlx_image);
	mlx_destroy_image(mlx->mlx, mlx->data->tex_ea.mlx_image);
	mlx_destroy_image(mlx->mlx, mlx->data->door.mlx_image);
	i = -1;
	while (++i < 21)
		mlx_destroy_image(mlx->mlx, mlx->data->spirit.aim[i].mlx_image);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_image(mlx->mlx, mlx->img.mlx_image);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_map(mlx->data);
	free(mlx->mlx);
}
