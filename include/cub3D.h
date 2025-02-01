/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:53:02 by zelkalai          #+#    #+#             */
/*   Updated: 2025/01/26 11:55:06 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <get_next_line_bonus.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs_helper.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>
#include <stdbool.h>


#define M_EMSG1 "Error\nDupping the map!\n"
#define M_EMSG2 "Error\nThe map is not closed!\n"
#define M_EMSG3 "Error\nToo many player Symbols on the map\n"
#define M_EMSG4 "Error\nNo player on the map\n"
#define M_EMSG5 "Error\nInvalid character on the map\n"
#define M_EMSG6 "Error\nFloor RGB values out of range 0-255\n"
#define M_EMSG7 "Error\nCeiling RGB values out of range 0-255\n"

# define SCREEN_HEIGHT 480
# define SCREEN_WIDTH 640
# define MINIMAP_SCALE 0.3
# define NUM_RAYS SCREEN_WIDTH
# define FOV 1.0471975512
# define OFFSET 4
# define MAX_KEYS 7
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.1
# define PITCH_FACTOR 1

typedef struct s_pl
{
	double			x;
	double			y;
	double			angle;
}					t_pl;

typedef struct s_img
{
	void			*mlx_image;
	char			*image_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct s_spirit
{
	t_img			aim[21];
	int				animating;
	int				current_frame;
	unsigned long	last_frame;

}					t_spirit;

typedef struct s_data
{
	struct s_mlx	*mlx;
	t_pl			*player;
	int				pixel_size;
	int				key_pressed[MAX_KEYS];
	char			**map;
	int				map_w;
	int				map_h;
	char			*f;
	char			*c;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	t_img			tex_no;
	t_img			tex_so;
	t_img			tex_ea;
	t_img			tex_we;
	int				mouse_moving;
	int				last_mouse_x;
	unsigned long	last_mouse_time;
	t_spirit		spirit;
	t_img			door;
}					t_data;

typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_data			*data;
	t_pl			*player;
}					t_mlx;

/*main.c*/
int					red_cross(t_mlx *mlx);
void				ray_casting(t_mlx *mlx, t_data *data);
int					game_loop(t_mlx *mlx);
int					init(t_mlx *mlx, t_data *data, char *argv, t_pl *player);

/*free.c*/
void				free_map(t_data *data);
void				clean_all(t_mlx *mlx);

/*load_texture.c*/
t_img				load_texture(t_mlx *mlx, char *path);
void				get_texture(t_mlx *mlx, t_data *data);

/*parse_map.c*/
int					count_lines(int fd);
char				*get_parameters(int fd, t_data *data);
int					check_player_position(t_data *data, int i, int j, int *p);
int					ft_ft(int fd, t_data *data);
int					set_map(char *file, t_data *data);
int					check_file(char *file);

/****************************************************/
/////////////////*   PARSE MORE *////////////////////
/****************************************************/

/*parse_maputils.c*/
int					map_invalid(char *file);
bool				map_closed(char **map, int map_height);
int					valid_map_chars(char **map);
bool				player_hadar(char **map);
bool				check_cell(int x, int y, char **map, int ht);

/*parse_more_utils.c*/
char				*get_first_line(int fd);
char				*dup_mline(char *line);
bool				is_valid_cell(int x, int y, char **map, int map_height);
bool				invalid_mapchar(char c);
bool				is_player_char(char c);

/*parse_configs.c*/
int					check_configs(t_data *data);
int					check_fnc(t_data *data);
int					check_texture(t_data *data);
int					invalid_fcchar(char *str);
int					check_rgb_num(t_data *data);

/*parse_configs_utils.c*/
bool				invalid_char(char c);
int					ft_check_bound(char **ptr);
bool				iswhite_space(char c);
bool				ft_isdigit_two(char c);
char				**strdup_map(int fd, int lcount);

/*free.c*/
void				double_free(char **args);
int					free_error_fd(char *msg, char **map, int fd, int fd2);
int					error_tf(char *msg, char **cvalue, char **fvalue);
int					error_msg(char *msg, int status);

//////////////////////////////////////////
                /*******/
/////////////////////////////////////////

int					parse(char *file, t_data *data);

/*mouse.c*/
int					mouse_rotation(int x, int y, t_data *data);
int					mouse_click(int keycode, int x, int y, t_data *data);
void				wait_for_frame(t_data *data);
void				check_frame(t_mlx *mlx);
void				left_click(t_mlx *mlx);

/*keys.c*/
void				check_door(t_data *data);
void				key_mouvment(t_mlx *mlx);
int					key_rotation(t_mlx *mlx);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);

/*keys_helper.c*/
unsigned long		get_current_time(void);
void				get_direction_vector(double angle, double *dx, double *dy);
int					check_corner(t_data *data, t_mlx *mlx, double new_x,
						double new_y);
void				collision_detection(t_mlx *mlx, double *new_x,
						double *new_y);
void				change_x_y(t_mlx *mlx, t_key_mouvment *k);

/*draw_minimap.c*/
void				draw_circle(t_mlx *mlx);
void				pixel_put(t_mlx *mlx, double map_x, double map_y,
						int color);
void				draw_minimap(t_mlx *mlx, t_data *data);
void				draw_rays(t_mlx *mlx, t_data *data);

/*draw_minimap_helper.c*/
int					calculate_pixel_size(void);
int					calculate_rays(t_mlx *mlx, t_data *data, t_draw_rays *d);

/*draw_3D_map.c*/
void				draw_wall_slice(t_mlx *mlx, t_draw_map *d, t_img *texture,
						int column);
void				init_ray_data_2(t_draw_map *d);
void				init_ray_data(t_draw_map *d, t_data *data);
void				get_wall_dist(t_draw_map *d, t_data *data);
void				draw_map(t_mlx *mlx, t_data *data);

/*draw_3D_map_helper.c*/
void				put_pixel_to_image(t_img img, int x, int y, int color);
int					get_tex_x(t_draw_map *d, t_img *texture);
int					get_texture_pixel(t_img *texture, int x, int y);
void				init_wall_slice(t_draw_wall_slice *w, t_draw_map *d,
						t_img *texture);

#endif
