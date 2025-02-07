/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:16:01 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 02:59:37 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	rgb_to_int(int red, int green, int blue)
{
	int	shifted_red;
	int	shifted_green;
	int	shifted_blue;
	int	result;

	shifted_red = red << 16;
	shifted_green = green << 8;
	shifted_blue = blue;
	result = shifted_red | shifted_green | shifted_blue;
	return (result);
}

int	rgb_final_check(t_data *data, char **c, char **f)
{
	int	i;

	i = -1;
	while (c[++i])
	{
		if (!is_digit_str(c[i]))
			return (printf("Error\nCeiling Numbers\n"), 1);
	}
	if (i != 3)
		return (printf("Error\nWrong Ceiling Vals Count\n"), 1);
	i = -1;
	while (f[++i])
	{
		if (!is_digit_str(c[i]))
			return (printf("Error\nFloor Numbers\n"), 1);
	}
	if (i != 3)
		return (printf("Error\nWrong Floor Vals Count\n"), 1);
	if (check_last_ch(data))
		return (1);
	return (0);
}

int	set_rgb_values(t_data *data, char **c, char **f)
{
	data->c_value = rgb_to_int(ft_atoi(c[0]), ft_atoi(c[1]), ft_atoi(c[2]));
	data->f_value = rgb_to_int(ft_atoi(f[0]), ft_atoi(f[1]), ft_atoi(f[2]));
	if (data->c_value < 0 || data->f_value < 0)
		return (printf("Error\nNegative RGB Values\n"), 0);
	if (data->c_value > MAX_RGB || data->f_value > MAX_RGB)
		return (printf("Error\nRGB Values Too Big\n"), 0);
	return (1);
}

int	is_digit_str(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (ft_isdigit_two(str[i]))
			flag++;
		i++;
	}
	if (flag)
		return (1);
	return (0);
}

int	check_last_ch(t_data *data)
{
	char	*c;
	char	*f;
	char	c_char;
	char	f_char;

	c = data->c;
	f = data->f;
	if (!c || !f)
		return (printf("Error\nNULL floor or ceiling ptr\n"), 1);
	c_char = data->c[ft_strlen(c) - 1];
	f_char = data->f[ft_strlen(f) - 1];
	if (!iswhite_space(c_char) && !ft_isdigit_two(c_char))
	{
		printf("Error\nLast char in ceiling configs\n");
		return (1);
	}
	if (!iswhite_space(f_char) && !ft_isdigit_two(f_char))
	{
		printf("Error\nLast char in floor configs\n");
		return (1);
	}
	return (0);
}
