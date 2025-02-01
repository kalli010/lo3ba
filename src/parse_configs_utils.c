/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:51:31 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/01 04:26:43 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool	invalid_char(char c)
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

char	**strdup_map(int fd, int lcount)
{
	int		i;
	char	**new;
	char	*line;

	new = malloc(sizeof(char *) * (lcount + 1));
	line = get_first_line(fd);
	if (!new || !line)
		return (NULL);
	i = 0;
	new[i] = dup_mline(line);
	while (++i < lcount)
	{
		line = get_next_line(fd);
		new[i] = dup_mline(line);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}
