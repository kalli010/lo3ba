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
# include <unistd.h>

# define SCREEN_HEIGHT 480
# define SCREEN_WIDTH 640
# define MINIMAP_SCALE 0.3
# define NUM_RAYS SCREEN_WIDTH
# define FOV 1.0471975512
# define OFFSET 5
# define MAX_KEYS 6
# define MOVE_SPEED 0.03
# define ROTATION_SPEED 0.03
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
int					parse(char *file, t_data *data);

/*keys.c*/
void				key_mouvment(t_mlx *mlx);
int					key_rotation(t_mlx *mlx);
int					key_press(int keycode, t_data *data);
int					key_release(int keycode, t_data *data);
int					red_cross(t_mlx *mlx);

/*keys_helper.c*/
void				get_direction_vector(double angle, double *dx, double *dy);
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
