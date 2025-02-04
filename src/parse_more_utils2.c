/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_more_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 05:32:22 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/03 05:32:29 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

bool    onlysp_orempty(char *mapl)
{
	int i;
	int flag;

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



////////////////

void    print_map(char **map)
{
	int i;
	// int j;

	i = 0;
	
	if (!map)
		return;
	while (map[i])
	{
		printf("i: [%d] line: [%s]\n", i, map[i]);
		i++;
	}
}

///////////////////////////////////
void print_data(t_data *data)
{
    if (data->f)
{        printf("data->F: [%s]\n", data->f);
}    if (data->c)
{        printf("data->C: [%s]\n", data->c);
}	if (data->no)
{		printf("data->no: [%s]\n", data->no);
}	if (data->so)
{        printf("data->so: [%s]\n", data->so);
}	if (data->we)
{        printf("data->we: [%s]\n", data->we);
}	if (data->ea)
{        printf("data->ea: [%s]\n", data->ea);
}

printf ("**F_val: [%d] \t C_VAL: [%d]**\n", data->f_value, data->c_value);

}


int duplicate_configs(char *file)
{
	int fd;
	int flag;
	char *line;

	fd = open (file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCan't open file: %s\n", file), 1);
	line = get_next_line(fd);
	flag = 0;
	while (line)
	{
		if (configs_found(line))
		{
			flag++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	if (flag > 6)
	{
		return(printf("Error\nToo many configs\n"), 1);
	}
	else if (flag < 6)
		return (printf("Error\nToo little configs\n"), 1);
	else
		return (0);
}

int configs_found(char *line)
{
	if (line[0] == 'F' || line[0] == 'C'
				|| (line[0] == 'N' && line[1] == 'O')
				|| (line[0] == 'S' && line[1] == 'O')
				|| (line[0] == 'W' && line[1] == 'E')
				|| (line[0] == 'E' && line[1] == 'A'))
	{
		return (1);
	}
	return (0);
}
