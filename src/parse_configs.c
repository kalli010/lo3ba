/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 02:51:15 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 23:20:14 by mel-atti         ###   ########.fr       */
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
	if (invalid_fc_line(data->c))
	{
		printf("Error\nInvalid RGB value in ceiling configs\n");
		return (1);
	}
	if (invalid_fc_line(data->f))
	{
		printf("Error\nInvalid RGB value in floor configs\n");
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
	if (trim_whitesp(data))
		return (printf("Error\ntrimming white spaces\n"), 1);
	if (check_extension(data))
		return (printf("Error\nTexture file must end with .xpm\n"), 1);
	if (open_tfiles_check(data))
		return (printf("Error\nCan't open files check texture\n"), 1);
	return (0);
}

int	invalid_fc_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (invalid_fc_char(str[i]) && str[i] != '\n')
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
		return (printf("Error\ncheck_rgb_num, ft_split!!!\n"), 1);
	if (ft_check_bound(fvalue))
		return (error_tf(M_EMSG6, cvalue, fvalue));
	if (ft_check_bound(cvalue))
		return (error_tf(M_EMSG7, cvalue, fvalue));
	if (rgb_final_check(data, cvalue, fvalue))
		return (error_tf(NULL, cvalue, fvalue));
	if (!set_rgb_values(data, cvalue, fvalue))
		return (error_tf(NULL, cvalue, fvalue));
	double_free(fvalue);
	double_free(cvalue);
	return (0);
}
