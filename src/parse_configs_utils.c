/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:51:31 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 23:24:09 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	invalid_fc_char(char c)
{
	if (c != ',' && !iswhite_space(c) && !ft_isdigit_two(c))
		return (true);
	else
		return (false);
}

int	ft_check_bound(char **ptr)
{
	int	num;
	int	i;

	i = 0;
	while (ptr[i])
	{
		num = ft_atoi(ptr[i]);
		if (num < 0 || num > 255)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

bool	iswhite_space(char c)
{
	if (c != 32 && c != '\t' && c != '\v')
		return (0);
	else
		return (1);
}

bool	ft_isdigit_two(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	valid_first_char(char c)
{
	if (c != 'F' && c != 'C' && c != 'N' && c != 'S'
		&& c != 'W' && c != 'E' && c != 'D' && c != 'B'
		&& c != '0' && c != '1' && !iswhite_space(c) && c != 10)
		return (0);
	return (1);
}
