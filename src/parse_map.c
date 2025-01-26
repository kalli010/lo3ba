#include <cub3D.h>

int count_lines(int fd)
{
  int i;
  int j;
  char *line;

  j = 0;
  line = get_next_line(fd);
  while(line)
  {
    i = 0;
    while(line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
      i++;
    if(line[i] == '1' || line[i] == '0')
      j++;
    free(line);
    line = get_next_line(fd);
  }
  return (j);
}

char *get_parameters(int fd, t_data *data)
{
  int i;
  char *line;

  line = get_next_line(fd);
  while(line)
  {
    i = 0;
    while(line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
      i++;
    if(line[i] && (line[i] == '0' || line[i] == '1'))
      return (line);
    else if(line[i] && line[i] == 'N')
      data->no = ft_strdup(&line[i + 3]);
    else if(line[i] && line[i] == 'S')
      data->so = ft_strdup(&line[i + 3]);
    else if(line[i] && line[i] == 'W')
      data->we = ft_strdup(&line[i + 3]);
    else if(line[i] && line[i] == 'E')
      data->ea = ft_strdup(&line[i + 3]);
    else if(line[i] && line[i] == 'F')
      data->f = ft_strdup(&line[i + 2]);
    else if(line[i] && line[i] == 'C')
      data->c = ft_strdup(&line[i + 2]);
    free(line);
    line = get_next_line(fd);
  }
  return (NULL);
}

int check_player_position(t_data *data, int i, int j, int *p)
{
  if (data->map[i][j] == 'N')
    data->player->angle = 3 * M_PI / 2;
  else if (data->map[i][j] == 'S')
    data->player->angle = M_PI / 2;
  else if (data->map[i][j] == 'E')
    data->player->angle = 0;
  else if (data->map[i][j] == 'W')
    data->player->angle = M_PI;
  data->map[i][j] = 'P';
  data->player->x = j + 0.5;
  data->player->y = i + 0.5;
  (*p)++;
  return (0);
}

int ft_ft(int fd, t_data *data, t_pl *player)
{
  int i;
  char *line;
  int j;
  int p;

  line = get_parameters(fd, data);
  p = 0;
  i = 0;
  while(line)
  {
    data->map[i] = line;
    j = -1;
    data->map_w = 0;
    while(data->map[i][++j])
    {
      if(data->map[i][j] != '\n')
        data->map_w++;
      else
        data->map[i][j] = '\0';
      if(data->map[i][j] == 'N' || data->map[i][j] == 'S' \
        || data->map[i][j] == 'E' || data->map[i][j] == 'W')
        check_player_position(data, i, j, &p);
    }
    i++;
    line = get_next_line(fd);
  }
  if (p != 1)
    return (1);
  return (0);
}

/*set data*/
int set_map(char *file, t_data *data, t_pl *player)
{
  int fd1;
  int fd2;

  fd1 = open(file, O_RDONLY);
  fd2 = open(file, O_RDONLY);
  if(fd1 < 0 || fd2 < 0)
  {
    printf("Error\ncan't open the map's file.\n");
    return(1);
  }
  data->map_h = count_lines(fd1);
  data->map = (char **)malloc(sizeof(char *) * (data->map_h + 1));
  if (ft_ft(fd2, data, player))
    return (1);
  data->map[data->map_h] = NULL;
  close (fd1);
  close (fd2);
  return(0);
}

/*file checks*/
int check_file(char *file)
{
  int len;
  int j;

  len = ft_strlen(file);
  j = ft_strlen(".cub");
  if(len <= j || \
    ft_strncmp(&file[len - j], ".cub", j) || \
    ft_strchr(file, '/') == &file[ft_strlen(file) - 5])
  {
    printf("Error\nthe map file should be *.cub\n");
    return(1);
  }
  return(0);
}

/*lparsing*/
int parse(char *file, t_data *data, t_pl *player)
{
  data->map = NULL;
  if (check_file(file))
    return (1);
  if(set_map(file, data, player))
    return(1);
  return(0);
}
