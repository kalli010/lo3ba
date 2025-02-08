/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:14:43 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 23:22:32 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_first_char(char *file)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nOpen fd check_1st_char\n"), 1);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && iswhite_space(line[i]))
			i++;
		if (!valid_first_char(line[i]))
			return (free(line), error_msg(M_EMSG9, 1));
		if (!valid_following_chars(&line[i]))
			return (free(line), error_msg(M_EMSG9, 1));
		free (line);
		line = get_next_line(fd);
	}
	return (0);
}

int	valid_following_chars(char *line)
{
	if (line[0] == 'F' || line[0] == 'C')
	{
		if (invalid_fc_line(&line[1]))
			return (0);
	}
	else if (line[0] == 'N' || line[0] == 'S'
		|| line[0] == 'W' || line[0] == 'E'
		|| line[0] == 'D' || line[0] == 'B')
	{
		if (invalid_nsew_line(line))
			return (0);
	}
	else if (line[0] == '0' || line[0] == '1' || iswhite_space(line[0]))
	{
		if (invalid_sp01(line))
			return (0);
	}
	return (1);
}

int	invalid_nsew_line(char *line)
{
	if (!line)
		return (1);
	if (line[0] == 'N' || line[0] == 'S')
	{
		if (line[1] == 'O')
			return (0);
		return (nsew_check(&line[1]));
	}
	else if (line[0] == 'W')
	{
		if (line[1] == 'E')
			return (0);
		return (nsew_check(&line[1]));
	}
	else if (line[0] == 'E')
	{
		if (line[1] == 'A')
			return (0);
		return (nsew_check(&line[1]));
	}
	else if (line[0] == 'D' || line[0] == 'B')
		return (nsew_check(&line[1]));
	return (0);
}

int	nsew_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && !iswhite_space(line[i])
			&& line[i] != 'D' && line[i] != 'B')
			return (1);
		i++;
	}
	return (0);
}

int	invalid_sp01(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && !iswhite_space(line[i])
			&& line[i] != 'D' && line[i] != 'B' && !is_player_char(line[i]))
			return (1);
		i++;
	}
	return (0);
}
