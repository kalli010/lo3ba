/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 04:18:18 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 04:18:49 by mel-atti         ###   ########.fr       */
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
	if (ft_strncmp(&str[len], ".xpm", 4))       //// THE Q IS IS'T A 4 OR 5?
	{
		return (1);
	}
	return (0);
}

int trim_whitesp(t_data *data)
{
	char *no;
	char *so;
	char *we;
	char *ea;

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