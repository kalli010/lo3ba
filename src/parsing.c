/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 02:49:24 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/07 02:51:36 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>


////////////////

static void    print_map(char **map)
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

static void print_data(t_data *data)
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

static void print_map_ndata(t_data *data)
{
	char **map = data->map;
	printf("***CURRENT MAP***\n");
	print_map(map);
	printf("***CURRENT DATA***\n");
	print_data(data);

}

/////////////////////////////

int	parse(char *file, t_data *data)
{
	data->map = NULL;
	if (check_file(file))
		return (1);
	if (duplicate_configs(file))
		return (1);
	if (map_invalid(file))
		return (1);
	if (set_map(file, data))
		return (1);
	if (check_configs(data))
		return (1);
	if (check_first_char(file))
		return (1);
	data->mini_map = get_new_map(file);
	if (!data->mini_map)
		return (printf("Error\nmini_map\n"), 1);
	
	///////////////////
	print_map_ndata(data);
	//////////////////
	return (0);
}

int	check_file(char *file)
{
	int	len;
	int	j;

	len = ft_strlen(file);
	j = ft_strlen(".cub");
	if (len <= j || ft_strncmp(&file[len - j], ".cub", j) || ft_strchr(file,
			'/') == &file[ft_strlen(file) - 5])
	{
		printf("Error\nthe map file should be *.cub\n");
		return (1);
	}
	return (0);
}

int	set_map(char *file, t_data *data)
{
	int	fd1;
	int	fd2;

	fd1 = open(file, O_RDONLY);
	fd2 = open(file, O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error\ncan't open the map's file.\n");
		return (1);
	}
	data->map_h = count_map_lines(fd1);
	data->map = (char **)malloc(sizeof(char *) * (data->map_h + 1));
	if (ft_ft(fd2, data))
		return (1);
	data->map[data->map_h] = NULL;
	close(fd1);
	close(fd2);
	return (0);
}

int	scape_spaces(char *line)
{
	int	i;

	i = 2;
	while (line[i] == ' ')
		i++;
	return (i);
}

char	*get_texture_data(char *line, int i)
{
	char	*data;

	i += scape_spaces(&line[i]);
	data = ft_strdup(&line[i]);
	if (!data)
	{
		printf("Error\nStrdup get texture data\n");
		return (NULL);
	}
	return (data);
}
