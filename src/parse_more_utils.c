/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:52:21 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 02:44:29 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	count_map_lines(int fd)
{
	int		i;
	int		j;
	char	*line;
	int		ws_flag;

	j = 0;
	line = get_first_line(fd);
	while (line)
	{
		i = 0;
		ws_flag = 0;
		while (line[i] && iswhite_space(line[i]))
		{
			ws_flag++;
			i++;
		}
		if (ws_flag && line[i] == '\0')
			j++;
		if (line[i] == '1' || line[i] == '0')
			j++;
		free(line);
		line = get_next_line(fd);
	}
	return (j);
}

char	**strdup_map(int fd, int lcount)
{
	int		i;
	char	**new;
	char	*line;

	new = malloc(sizeof(char *) * (lcount + 2));
	if (!new)
		return (printf("Error\nStrdup_map()\n"), NULL);
	line = get_first_line(fd);
	if (!line)
		return (printf("Error\nThere's no 1st map's line\n"), NULL);
	new[0] = dup_mline(line);
	i = 1;
	while (i <= lcount)
	{
		line = get_next_line(fd);
		new[i] = dup_mline(line);
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	*get_first_line(int fd)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] && (line[i] == '0' || line[i] == '1'))
			{
				return (line);
			}
			else if (invalid_mapchar(line[i]))
				break ;
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
	char	*new;

	i = 0;
	if (!line)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new)
		return (NULL);
	while (line[i])
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
	if (line[i] == '\0')
		new[i] = '\0';
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
