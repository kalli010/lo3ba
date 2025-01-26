/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:27:24 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:27:25 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

t_img	load_texture(t_mlx *mlx, char *path)
{
	t_img	texture;

	texture.mlx_image = mlx_xpm_file_to_image(mlx->mlx, path, &texture.width,
			&texture.height);
	if (!texture.mlx_image)
	{
		printf("failed to load %s\n", path);
		exit(1);
	}
	texture.image_data = mlx_get_data_addr(texture.mlx_image,
			&texture.bits_per_pixel, &texture.size_line, &texture.endian);
	return (texture);
}

void	get_texture(t_mlx *mlx, t_data *data)
{
	data->tex_no = load_texture(mlx, data->no);
	data->tex_so = load_texture(mlx, data->so);
	data->tex_ea = load_texture(mlx, data->ea);
	data->tex_we = load_texture(mlx, data->we);
}
