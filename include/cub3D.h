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

#define SCREEN_HEIGHT 480
#define SCREEN_WIDTH 640
#define MINIMAP_SCALE 0.3
#define NUM_RAYS SCREEN_WIDTH
#define FOV (M_PI / 3)
#define OFFSET 5
#define MAX_KEYS 6
#define MOVE_SPEED 0.03
#define ROTATION_SPEED 0.03
#define PITCH_FACTOR 1

typedef struct s_pl
{
  double x;
  double y;
  double angle;
} t_pl;

typedef struct s_img
{
  void *mlx_image;
  char *image_data;
  int bits_per_pixel;
  int size_line;
  int endian;
  int width;
  int height;
} t_img;

typedef struct s_data
{
  struct s_mlx *mlx;
  t_pl *player;
  int pixel_size;
  int key_pressed[MAX_KEYS];
  char **map;
  int map_w;
  int map_h;
  char *f;
  char *c;
  char *no;
  char *so;
  char *ea;
  char *we;
  t_img tex_no;
  t_img tex_so;
  t_img tex_ea;
  t_img tex_we;
} t_data;

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
int redraw_map(t_mlx *mlx, t_data *data, double new_x, double new_y);
void get_direction_vector(double angle, double *dx, double *dy);
int collision_detection(t_mlx *mlx, double *new_x, double *new_y);
int key_mouvment(t_mlx *mlx);
int key_rotation(t_mlx *mlx);
int key_release(int keycode, t_data *data);
int key_press(int keycode, t_data *data);
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
void draw_wall_slice(t_mlx *mlx, t_draw_map *d, t_img *texture, int column);
int get_texture_pixel(t_img *texture, int x, int y);
void draw_map(t_mlx *mlx, t_data *data);
void draw_rays(t_mlx *mlx, t_data *data);
int pixel_put(t_mlx *mlx, double x, double y, int color);
int draw_minimap(t_mlx *mlx, t_data *data);
int calculate_pixel_size(t_data *data);
int ray_casting(t_mlx *mlx, t_data *data, t_pl *player);

#endif
