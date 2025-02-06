/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maputils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:51:59 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/01 04:24:47 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	map_invalid(char *file)
{
	char	**map;
	int		fd;
	int		fd2;
	int		lcount;

	fd = open(file, O_RDONLY);
	fd2 = open(file, O_RDONLY);
	if (fd < 0 || fd2 < 0)
		return (printf("Error\nOpening the file map_invalid\n"), 1);
	lcount = count_map_lines(fd2);
	if (lcount <= 0)
		return (free_error_fd(M_EMSG8, NULL, fd, fd2));
	map = strdup_map(fd, lcount);
	if (!map)
		return (free_error_fd(NULL, NULL, fd, fd2));
	if (!map_closed(map, lcount))
		return (free_error_fd(M_EMSG2, map, fd, fd2));
	if (!valid_map_chars(map))
		return (free_error_fd(M_EMSG5, map, fd, fd2));
	if (!player_hadar(map))
		return (free_error_fd(NULL, map, fd, fd2));
	free_error_fd(NULL, map, fd, fd2);
	return (0);
}

bool	map_closed(char **map, int ht)
{
	int	y;
	int	x;
	int	len;

	y = -1;
	len = 0;
	while (++y < ht)
	{
		if (onlysp_orempty(map[y]))
			return (false);

		x = -1;
		while (++x < (int)ft_strlen(map[y]))
		{
			if (map[y][x] == '0' || is_player_char(map[y][x]))
			{
				len = (int)ft_strlen(map[y]) - 1;
				if (x == 0 || x == len || y == 0 || y == ht - 1)
				{
					return (false);
				}
				if (!check_cell(x, y, map, ht))
					return (false);
			}
		}
	}
	return (true);
}

int	valid_map_chars(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (invalid_mapchar(map[i][j]))
			{
				flag++;
			}
		}
	}
	if (flag)
		return (0);
	return (1);
}

bool	player_hadar(char **map)
{
	int	i;
	int	j;
	int	flag;

	i = -1;
	flag = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (is_player_char(map[i][j]))
				flag++;
		}
	}
	if (flag > 1)
		return (error_msg(M_EMSG3, 0));
	if (!flag)
		return (error_msg(M_EMSG4, 0));
	return (1);
}

bool	check_cell(int x, int y, char **map, int ht)
{
	if (!is_valid_cell(x, y - 1, map, ht) || map[y - 1][x] == ' ')
		return (false);
	if (!is_valid_cell(x, y + 1, map, ht) || map[y + 1][x] == ' ')
		return (false);
	if (!is_valid_cell(x - 1, y, map, ht) || map[y][x - 1] == ' ')
		return (false);
	if (!is_valid_cell(x + 1, y, map, ht) || map[y][x + 1] == ' ')
		return (false);
	else
		return (true);
}
