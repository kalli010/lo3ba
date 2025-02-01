/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:52:21 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/01 04:25:43 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char	*get_first_line(int fd)
{
	int		i;
	int		j;
	char	*line;

	line = get_next_line(fd);
	j = 0;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] && (line[i] == '0' || line[i] == '1'))
			{
				j = i + 1;
				if (line[j] && (line[j] == '0' || line[j] == '1'))
					return (line);
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

char	*dup_mline(char *line)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(line) + 1;
	new = malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	while (i < len && line[i])
	{
		if (line[i] == '\n')
		{
			new[i] = '\0';
			break ;
		}
		else
			new[i] = line[i];
		i++;
	}
	free(line);
	return (new);
}

bool	is_valid_cell(int x, int y, char **map, int map_height)
{
	if (y < 0 || y >= map_height)
	{
		return (false);
	}
	if (x < 0 || x >= (int)ft_strlen(map[y]))
	{
		return (false);
	}
	return (true);
}

bool	invalid_mapchar(char c)
{
	if (c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == '0' || c == '1')
	{
		return (0);
	}
	return (1);
}

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}
