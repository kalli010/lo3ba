#ifndef CUB3D_H
# define CUB3D_H

#include <structs_helper.h>
#include <libft.h>
#include <get_next_line_bonus.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define MINIMAP_SCALE 0.2
#define NUM_RAYS SCREEN_WIDTH
#define FOV (M_PI / 3)

typedef struct s_pl
{
  float x;
  float y;
  float angle;
} t_pl;

typedef struct s_data
{
  char *no;
  char *so;
  char *ea;
  char *we;
  char *f;
  char *c;
  char **map;
  int map_w;
  int map_h;
  int pixel_size;
  t_pl *player;
} t_data;

typedef struct s_img
{
  void *mlx_image;
  char *image_data;
  int bits_per_pixel;
  int size_line;
  int endian;
} t_img;

typedef struct s_mlx
{
  void *mlx;
  void *win;
  t_img img;
  t_data *data;
  t_pl *player;
} t_mlx;

/*main.c*/
void free_map(t_data *data);
void clean_all(t_mlx *mlx);
int main(int argc, char **argv);

/*keys.c*/
int redraw_map(t_mlx *mlx, t_data *data, float new_x, float new_y);
void get_direction_vector(float angle, float *dx, float *dy);
int collision_detection(t_mlx *mlx, float *new_x, float *new_y);
int key_mouvment(int keycode, t_mlx *mlx);
int key_rotation(int keycode, t_mlx *mlx);
int keys(int keycode, t_mlx *mlx);
int red_cross(int keycode, t_mlx *mlx);

/*parse_map.c*/
int count_lines(int fd);
char *get_parameters(int fd, t_data *data);
int check_player_position(t_data *data, int i, int j, int *p);
int ft_ft(int fd, t_data *data, t_pl *player);
int set_map(char *file, t_data *data, t_pl *player);
int check_file(char *file);
int parse(char *file, t_data *data, t_pl *player);

/*ray_csting.c*/
//int draw_wall_slice(t_mlx *mlx, float distance, int i, int wall_color);
void draw_map(t_mlx *mlx, t_data *data);
void draw_rays(t_mlx *mlx, t_data *data);
int pixel_put(t_mlx *mlx, float x, float y, int color);
int draw_minimap(t_mlx *mlx, t_data *data);
int calculate_pixel_size(t_data *data);
int ray_casting(t_mlx *mlx, t_data *data, t_pl *player);

#endif
