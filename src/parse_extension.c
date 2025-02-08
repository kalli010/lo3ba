/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 04:18:18 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 23:48:50 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_extension(t_data *data)
{
	if (invalide_extension(data->no) || invalide_extension(data->so)
		|| invalide_extension(data->we) || invalide_extension(data->ea))
	{
		return (1);
	}
	return (0);
}

int	invalide_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	while (str[len] != '.' && len > 0)
		len--;
	if (ft_strncmp(&str[len], ".xpm", 4))
	{
		return (1);
	}
	return (0);
}

int	trim_whitesp(t_data *data)
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;

	no = data->no;
	so = data->so;
	we = data->we;
	ea = data->ea;
	if (!no || !so || !we || !ea)
		return (1);
	data->no = ft_strtrim(no, " ");
	data->so = ft_strtrim(so, " ");
	data->we = ft_strtrim(we, " ");
	data->ea = ft_strtrim(ea, " ");
	return (0);
}

int	open_tfiles_check(t_data *data)
{
	int	i;
	int	fd[4];

	fd[0] = open(data->no, O_RDONLY);
	fd[1] = open(data->so, O_RDONLY);
	fd[2] = open(data->we, O_RDONLY);
	fd[3] = open(data->ea, O_RDONLY);
	i = -1;
	while (++i < 4)
	{
		if (fd[i] < 0)
		{
			i = -1;
			while (++i < 4)
				close(fd[i]);
			return (1);
		}
	}
	i = -1;
	while (++i < 4)
		close(fd[i]);
	return (0);
}
