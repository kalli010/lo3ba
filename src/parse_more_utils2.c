/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:32:22 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 23:26:46 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	onlysp_orempty(char *mapl)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (ft_strlen(mapl) <= 0)
		return (1);
	while (mapl[++i])
	{
		if (mapl[i] == '0' || mapl[i] == '1')
			flag++;
	}
	if (!flag)
		return (1);
	return (0);
}

bool	invalid_mapchar(char c)
{
	if (!is_player_char(c) && !iswhite_space(c) && c != '0' && c != '1'
		&& c != 'D' && c != 'B')
	{
		return (1);
	}
	return (0);
}

bool	is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	duplicate_configs(char *file)
{
	int		fd;
	int		flag;
	char	*line;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCan't open file: %s\n", file), 1);
	line = get_next_line(fd);
	flag = 0;
	while (line)
	{
		if (configs_found(line))
			flag++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (flag > 6)
		return (printf("Error\nToo many configs\n"), 1);
	else if (flag < 6)
		return (printf("Error\nToo little configs\n"), 1);
	else
		return (0);
}

int	configs_found(char *line)
{
	int	i;

	i = 0;
	while (line[i] && iswhite_space(line[i]))
		i++;
	if (line[i] == 'F' || line[i] == 'C'
		|| (line[i] == 'N' && line[i + 1] == 'O')
		|| (line[i] == 'S' && line[i + 1] == 'O')
		|| (line[i] == 'W' && line[i + 1] == 'E')
		|| (line[i] == 'E' && line[i + 1] == 'A'))
	{
		return (1);
	}
	return (0);
}
