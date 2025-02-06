/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:15:13 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/06 05:15:19 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

int	count_lines(int fd)
{
	int		i;
	int		j;
	char	*line;

	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] == '1' || line[i] == '0')
			j++;
		free(line);
		line = get_next_line(fd);
	}
	return (j);
}

int scape_spaces(char *line)
{
  int i;

  i = 2;
  while (line[i] == ' ')
    i++;
  return(i);
}

char	*get_parameters(int fd, t_data *data)
{
	int		i;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		if (line[i] && (line[i] == '0' || line[i] == '1'))
			return (line);
		else if (line[i] && line[i] == 'N' && line[i + 1] == 'O')
    {
      i += scape_spaces(&line[i]);
      data->no = ft_strdup(&line[i]);
    }
		else if (line[i] && line[i] == 'S' && line[i + 1] == 'O')
    {
      i += scape_spaces(&line[i]);
			data->so = ft_strdup(&line[i]);
    }
		else if (line[i] && line[i] == 'W' && line[i + 1] == 'E')
    {
      i += scape_spaces(&line[i]);
			data->we = ft_strdup(&line[i]);
    }
		else if (line[i] && line[i] == 'E' && line[i + 1] == 'A')
    {
      i += scape_spaces(&line[i]);
			data->ea = ft_strdup(&line[i]);
    }
		else if (line[i] && line[i] == 'F')
    {
      i += scape_spaces(&line[i]);
			data->f = ft_strdup(&line[i]);
    }
		else if (line[i] && line[i] == 'C')
    {
      i += scape_spaces(&line[i]);
			data->c = ft_strdup(&line[i]);
    }
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

int	check_player_position(t_data *data, int i, int j, int *p)
{
	// if (data->map[i][j] == 'N')
	if (data->map[i][j] == 'N' && data->map[i][j + 1] != 'O') //// // /
		data->player->angle = 3 * M_PI / 2;
	else if (data->map[i][j] == 'S' && data->map[i][j + 1] != 'O')
		data->player->angle = M_PI / 2;
	else if (data->map[i][j] == 'E' && data->map[i][j + 1] != 'A')
		data->player->angle = 0;
	else if (data->map[i][j] == 'W' && data->map[i][j + 1] != 'E')
		data->player->angle = M_PI;
	data->map[i][j] = '0';
	data->player->x = j + 0.5; ///
	data->player->y = i + 0.5; ///
	(*p)++; // will always increment even if there is no player!!?
	return (0);
}

// parse player:
// traverse to the start of the map
// checks if there is a palyer on the map
int	ft_ft(int fd, t_data *data)
{
	int		i;
	char	*line;
	int		j;
	int		p;

	line = get_parameters(fd, data);
	p = 0;
	i = 0;

	while (line && i < data->map_h)
	{
		data->map[i] = line;
		j = -1;
		data->map_w = 0;
		while (data->map[i][++j])
		{
			if (data->map[i][j] != '\n')
				data->map_w++;
			else
				data->map[i][j] = '\0';
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				check_player_position(data, i, j, &p);
		}
		i++;
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (p != 1)
		return (1);
	data->map[i] = NULL;
	return (0);
}


/*set data*/
int	set_map(char *file, t_data *data)
{
	int	fd1;
	int	fd2;
	// int fd3;

	fd1 = open(file, O_RDONLY);
	fd2 = open(file, O_RDONLY);	
	// fd3 = open(file, O_RDONLY);	
	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error\ncan't open the map's file.\n");
		return (1);
	}
	// data->map_h = count_lines(fd1);
	data->map_h = count_map_lines(fd1);
	data->map = (char **)malloc(sizeof(char *) * (data->map_h + 1));
	// data->map = strdup_map(fd3, data->map_h);
	if (ft_ft(fd2, data)) //
		return (1);
	data->map[data->map_h] = NULL;
	close(fd1);
	close(fd2);
	return (0);
}

/*file checks*/
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


/*lparsing*/
int	parse(char *file, t_data *data)
{
	data->map = NULL;
	if (check_file(file))
		return (1);
	if (duplicate_configs(file))
		return (1);
	if (map_invalid(file)) //
		return (1);
	if (set_map(file, data))
		return (1);
	if (check_configs(data)) //
		return (1);
	if (check_first_char(file))
		return (1);
	
	data->mini_map = get_new_map(file);
	if (!data->mini_map)
		return (printf("Error\nmini_map\n"), 1);


    /** printing **/
	printf("data->map 1\n");
	print_map(data->map);
	print_data(data); ///////

	printf("data->mini_map 2\n");
	print_map(data->mini_map);

	return (0);
}

//////////////////////////////////////////////

