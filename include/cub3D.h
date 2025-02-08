/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelkalai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:53:02 by zelkalai          #+#    #+#             */
/*   Updated: 2025/02/07 22:50:35 by zelkalai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <get_next_line_bonus.h>
# include <libft.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <structs_helper.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# define M_EMSG2 "Error\nThe map is not closed!\n"
# define M_EMSG3 "Error\nToo many player Symbols on the map\n"
# define M_EMSG4 "Error\nNo player on the map\n"
# define M_EMSG5 "Error\nInvalid character on the map\n"
# define M_EMSG6 "Error\nFloor RGB values out of range 0-255\n"
# define M_EMSG7 "Error\nCeiling RGB values out of range 0-255\n"
# define M_EMSG8 "Error\nThere's No Map\n"
# define M_EMSG9 "Error\nWrong configs\n"
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
# define MAX_RGB 16777215

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
	char			**mini_map;
	int				f_value;
	int				c_value;
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
void				double_free(char **args);
int					free_error_fd(char *msg, char **map, int fd, int fd2);
int					error_tf(char *msg, char **cvalue, char **fvalue);

/*free_utils.c*/
int					error_msg(char *msg, int status);

/*load_texture.c*/
void				init3(t_data *data);
t_img				load_texture(t_mlx *mlx, char *path);
void				get_texture(t_mlx *mlx, t_data *data);

/****************************************************/
/////////////////*   PARSE MORE *////////////////////
/****************************************************/

/*parse_map.c*/
int					ft_ft(int fd, t_data *data);
char				*get_parameters(int fd, t_data *data);
void				ft_ft_handle(t_data *data, int i, int j, int *p);
int					check_player_position(t_data *data, int i, int j, int *p);
void				get_texture_handle(char *line, int i, t_data *data);

/*parsing.c*/
int					parse(char *file, t_data *data);
int					check_file(char *file);
int					set_map(char *file, t_data *data);
int					scape_spaces(char *line);
char				*get_texture_data(char *line, int i);

/*parse_maputils.c*/
int					map_invalid(char *file);
bool				map_closed(char **map, int map_height);
int					valid_map_chars(char **map);
bool				player_hadar(char **map);
bool				check_cell(int x, int y, char **map, int ht);

/*parse_more_utils.c*/
int					count_map_lines(int fd);
char				**strdup_map(int fd, int lcount);
char				*get_first_line(int fd);
char				*dup_mline(char *line);
bool				is_valid_cell(int x, int y, char **map, int map_height);

/*parse_more_utils2.c*/
bool				onlysp_orempty(char *mapl);
bool				invalid_mapchar(char c);
bool				is_player_char(char c);
int					duplicate_configs(char *file);
int					configs_found(char *line);

/*parse_configs.c*/

int					check_configs(t_data *data);
int					check_fnc(t_data *data);
int					check_texture(t_data *data);
int					invalid_fc_line(char *str);
int					check_rgb_num(t_data *data);

/*parse_configs_utils.c*/
bool				invalid_fc_char(char c);
int					ft_check_bound(char **ptr);
bool				iswhite_space(char c);
bool				ft_isdigit_two(char c);
int					valid_first_char(char c);

/*parse_configs_more.c*/
int					check_first_char(char *file);
int					valid_following_chars(char *line);
int					invalid_nsew_line(char *line);
int					nsew_check(char *line);
int					invalid_sp01(char *line);

/*rgb_checks.c*/
int					rgb_to_int(int red, int green, int blue);
int					rgb_final_check(t_data *data, char **c, char **f);
int					set_rgb_values(t_data *data, char **c, char **f);
int					is_digit_str(char *str);
int					check_last_ch(t_data *data);

/*build_new_map.c*/
char				**get_new_map(char *file);
char				**fix_map(char **map, int longest_line, int lcount);
char				*fix_line(char **map, int i, int longest_line);
int					get_llenght(char **map);

/*parse_extension.c*/
int					check_extension(t_data *data);
int					invalide_extension(char *str);
int					trim_whitesp(t_data *data);
int					open_tfiles_check(t_data *data);
int					last_ftft_check(t_data *data, char *line, int p, int i);

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
int					count_map_w(t_data *data);
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
