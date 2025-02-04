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
		// else if (line[i] && line[i] == 'N')
		// 	data->no = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'S')
		// 	data->so = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'W')
		// 	data->we = ft_strdup(&line[i + 3]);
		// else if (line[i] && line[i] == 'E')
		// 	data->ea = ft_strdup(&line[i + 3]);

		else if (line[i] && line[i] == 'N' && line[i + 1] == 'O')
			data->no = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'S' && line[i + 1] == 'O')
			data->so = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'W' && line[i + 1] == 'E')
			data->we = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'E' && line[i + 1] == 'A')
			data->ea = ft_strdup(&line[i + 3]);
		else if (line[i] && line[i] == 'F')
			data->f = ft_strdup(&line[i + 2]);
		else if (line[i] && line[i] == 'C')
			data->c = ft_strdup(&line[i + 2]);
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

	while (line)
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
	if (p != 1)
		return (1);


	data->map[i] = NULL; //// // /


	return (0);
}


/*set data*/
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
	data->map_h = count_lines(fd1);
	data->map = (char **)malloc(sizeof(char *) * (data->map_h + 1));
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
	// if (check_first_char(file))
	// 	return (1);
	
	// printf("222222\n");
	print_map(data->map);
	print_data(data); ///////

	return (0);
}

// int check_first_char(char *file)
// {
// 	int fd;
// 	char *line;
// 	// int i;

// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (printf("ERRR\n"), 1);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (!valid_first_char(line[0]))
// 			return (printf("Error\n Wrong configs\n"), 1);
// 		free (line);
// 		line = get_next_line(fd);
// 	}
// 	return (0):
// }

// int valid_first_char(char c)
// {
// 	if (!invalid_mapchar(c) &&  )
// }
