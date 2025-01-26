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
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free_map(mlx->data);
	free(mlx->mlx);
}
