/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:11:25 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:51:19 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	red_cross(t_mlx *mlx)
{
	clean_all(mlx);
	exit(0);
	return (0);
}

/*---draw everything---*/
void	ray_casting(t_mlx *mlx, t_data *data)
{
	draw_map(mlx, mlx->data);
	data->pixel_size = calculate_pixel_size();
	draw_circle(mlx);
	draw_minimap(mlx, data);
	draw_rays(mlx, mlx->data);
}

int	game_loop(t_mlx *mlx)
{
	unsigned long	current_time;

	current_time = get_current_time();
	if (mlx->data->mouse_moving && current_time
		- mlx->data->last_mouse_time > 0)
	{
		mlx->data->mouse_moving = 0;
		mlx->data->key_pressed[4] = 0;
		mlx->data->key_pressed[5] = 0;
	}
	mlx_clear_window(mlx->mlx, mlx->win);
	ray_casting(mlx, mlx->data);
	left_click(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.mlx_image, 0, 0);
	key_mouvment(mlx);
	key_rotation(mlx);
	return (0);
}

int	init(t_mlx *mlx, t_data *data, char *argv, t_pl *player)
{
	int	i;

	mlx->data = data;
	mlx->player = player;
	data->player = player;
	data->mlx = mlx;
	data->mouse_moving = 0;
	data->last_mouse_time = 0;
	data->last_mouse_x = -1;
	i = -1;
	while (++i < 7)
		data->key_pressed[i] = 0;
	data->spirit.animating = 0;
	data->spirit.current_frame = 0;
	data->spirit.last_frame = 0;
	if (parse(argv, data))
		return (free_map(data), 1);
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (clean_all(mlx), 1);
	mlx->win = mlx_new_window(mlx->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "lo3ba");
	if (!mlx->win)
		return (clean_all(mlx), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_pl	player;
	t_data	data;

	if (argc == 2)
	{
		if (init(&mlx, &data, argv[1], &player))
			return (1);
		get_texture(&mlx, &data);
		mlx.img.mlx_image = mlx_new_image(mlx.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		mlx.img.image_data = mlx_get_data_addr(mlx.img.mlx_image,
				&mlx.img.bits_per_pixel, &mlx.img.size_line, &mlx.img.endian);
		mlx_hook(mlx.win, 2, 1L << 0, key_press, &data);
		mlx_hook(mlx.win, 3, 1L << 1, key_release, &data);
		mlx_hook(mlx.win, 6, 1L << 6, mouse_rotation, &data);
		mlx_hook(mlx.win, 4, 1L << 2, mouse_click, &data);
		mlx_hook(mlx.win, 17, 0, red_cross, &mlx);
		mlx_loop_hook(mlx.mlx, game_loop, &mlx);
		mlx_loop(mlx.mlx);
		return (0);
	}
	printf("expecting <./cub3d> <file.cub>\n");
	return (1);
}
