/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:51:15 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/01 03:25:28 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	check_configs(t_data *data)
{
	if (check_fnc(data))
		return (1);
	if (check_texture(data))
		return (1);
	return (0);
}

int	check_fnc(t_data *data)
{
	if (invalid_fcchar(data->c))
	{
		printf("Error\n invalid char in ceiling configs\n");
		return (1);
	}
	if (invalid_fcchar(data->f))
	{
		printf("Error\n invalid char in floor configs\n");
		return (1);
	}
	if (check_rgb_num(data))
	{
		return (1);
	}
	return (0);
}

int	check_texture(t_data *data)
{
	int	fd[4];
	int	i;

	fd[0] = open(data->no, O_RDONLY);
	fd[1] = open(data->so, O_RDONLY);
	fd[2] = open(data->we, O_RDONLY);
	fd[3] = open(data->ea, O_RDONLY);
	i = -1;
	while (++i < 4)
	{
		if (fd[i] < 0)
		{
			printf("Error\n can't open files\n");
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

int	invalid_fcchar(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (invalid_char(str[i]))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_rgb_num(t_data *data)
{
	char	**fvalue;
	char	**cvalue;

	fvalue = ft_split(data->f, ',');
	cvalue = ft_split(data->c, ',');
	if (!cvalue || !fvalue)
	{
		return (printf("Error\nMalloc!!!\n"), 1);
	}
	if (ft_check_bound(fvalue))
	{
		return (error_tf(M_EMSG6, cvalue, fvalue));
	}
	if (ft_check_bound(cvalue))
	{
		return (error_tf(M_EMSG7, cvalue, fvalue));
	}
	double_free(fvalue);
	double_free(cvalue);
	return (0);
}
