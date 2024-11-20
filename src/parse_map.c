#include <cub3D.h>

int ft_ft(int fd, t_mlx *mlx, int f)
{
  int i;
  char *line;

  i = 0;
  line = get_next_line(fd);
  while(line)
  {
    if(f == 1)
      mlx->map[i] = line;
    else
      free(line);
    i++;
    line = get_next_line(fd);
  }
  return (i);
}

int set_map(char *file, t_mlx *mlx)
{
  int fd;
  int i;

  fd = open(file, O_RDONLY);
  if(fd < 0)
  {
    printf("Error\ncan't open the map's file\n");
    return(1);
  }
  i = ft_ft(fd, NULL, 0);
  mlx->map = (char **)malloc(sizeof(char *) * i);
  ft_ft(fd, mlx, 1);
  mlx->map[i] = NULL;
  close (fd);
  return(0);
}

int check_file(char *file)
{
  int len;

  len = ft_strlen(file);
  if(file[len - 1] != 'b' || file[len - 2] != 'u' || file[len - 3] != 'c' \
    || file[len - 4] != '.' || file[len - 5] == '/')
  {
    printf("Error\nthe map file should be *.cub\n");
    return(1);
  }
  return(0);
}

int parse(char *file, t_mlx *mlx)
{
  mlx->map = NULL;
  if (check_file(file))
    return (1);
  if(set_map(file, mlx))
    return(1);
  return(0);
}
