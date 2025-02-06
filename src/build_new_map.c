/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_new_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-atti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:13:52 by mel-atti          #+#    #+#             */
/*   Updated: 2025/02/06 05:14:00 by mel-atti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3D.h>

char **get_new_map(char *file)
{
	int fd;
	int longest_line;
	int lcount;
	char **map;
	char **new_map;


	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nopen fd mini_map\n"), NULL);
	lcount = count_map_lines(fd);
	close (fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nOpening fd mini_map\n"), NULL);

	map = strdup_map(fd, lcount);
	longest_line = get_llenght(map);

	new_map = fix_map(map, longest_line, lcount);
	if (!new_map)
		return (printf("Error\nCan't fix the map\n"), NULL);
	double_free (map);
	close(fd);
	// close(fd2);
	return (new_map);
}

char **fix_map(char **map, int longest_line, int lcount)
{
	char **new;
	int i;

	new = malloc(sizeof(char *) * (lcount + 2));
	i = 0;
	if (!new)
		return (printf("Error\nFix_map()\n"), NULL);
	while (i < lcount)
	{
		new[i] = fix_line(map, i, longest_line);
		i++;
	}
	new[i] = NULL;
	return(new);
}

char *fix_line(char **map, int i, int longest_line)
{
	char *new_line;
	int j;

	j = 0;
	new_line = malloc(sizeof (char) * (longest_line + 1));
	if (!new_line)
		return (printf("Error\nFix_line()\n"), NULL);

	while (map[i][j] != '\0')
	{
		if (iswhite_space(map[i][j]))
			new_line[j] = '1';
		else
			new_line[j] = map[i][j];
		j++;
	}
	while (j < longest_line)
	{
		new_line[j] = '1';
		j++;
	}
	new_line[j] = '\0';

	return (new_line);
}

int get_llenght(char **map)
{
	int longest;
	int i;
	int j;

	longest = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			j++;
		}
		if (j > longest)
			longest = j;
		i++;
	}
	return (longest);
}
