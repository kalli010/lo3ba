/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:15:13 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 02:39:44 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	ft_ft(int fd, t_data *data)
{
	int		i;
	char	*line;
	int		j;
	int		p;

	line = get_parameters(fd, data);
	p = 0;
	i = 0;
	while (line && i < data->map_h)
	{
		data->map[i] = line;
		j = -1;
		data->map_w = 0;
		while (data->map[i][++j])
			ft_ft_handle(data, i, j, &p);
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (p != 1)
		return (1);
	data->map[i] = NULL;
	return (0);
}

char	*get_parameters(int fd, t_data *data)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] && (line[i] == '0' || line[i] == '1'))
			return (line);
		else if (line[i] && (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
				|| line[i] == 'E' || line[i] == 'F' || line[i] == 'C'))
		{
			get_texture_handle(line, i, data);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	ft_ft_handle(t_data *data, int i, int j, int *p)
{
	if (data->map[i][j] != '\n')
		data->map_w++;
	else
		data->map[i][j] = '\0';
	if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
		|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
	{
		check_player_position(data, i, j, p);
	}
}

int	check_player_position(t_data *data, int i, int j, int *p)
{
	if (data->map[i][j] == 'N' && data->map[i][j + 1] != 'O')
		data->player->angle = 3 * M_PI / 2;
	else if (data->map[i][j] == 'S' && data->map[i][j + 1] != 'O')
		data->player->angle = M_PI / 2;
	else if (data->map[i][j] == 'E' && data->map[i][j + 1] != 'A')
		data->player->angle = 0;
	else if (data->map[i][j] == 'W' && data->map[i][j + 1] != 'E')
		data->player->angle = M_PI;
	data->map[i][j] = '0';
	data->player->x = j + 0.5;
	data->player->y = i + 0.5;
	(*p)++;
	return (0);
}

void	get_texture_handle(char *line, int i, t_data *data)
{
	if (line[i] && line[i] == 'N' && line[i + 1] == 'O')
		data->no = get_texture_data(line, i);
	else if (line[i] && line[i] == 'S' && line[i + 1] == 'O')
		data->so = get_texture_data(line, i);
	else if (line[i] && line[i] == 'W' && line[i + 1] == 'E')
		data->we = get_texture_data(line, i);
	else if (line[i] && line[i] == 'E' && line[i + 1] == 'A')
		data->ea = get_texture_data(line, i);
	else if (line[i] && line[i] == 'F')
		data->f = get_texture_data(line, i);
	else if (line[i] && line[i] == 'C')
		data->c = get_texture_data(line, i);
}
