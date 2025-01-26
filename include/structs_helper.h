#ifndef STRUCTS_HELPER_H
# define STRUCTS_HELPER_H

#include <cub3D.h>

typedef struct s_draw_map
{
  double start_angle;
  double angle_step;
  double p_x;
  double p_y;
  double ray_angle;
  double ray_x;
  double ray_y;
  double dist_x;
  double dist_y;
  int map_x;
  int map_y;
  int step_x;
  int step_y;
  double side_dist_y;
  double side_dist_x;
  int i;
  int side;
  double wall_dist;
  double wall_x;
  double wall_h;
} t_draw_map;

typedef struct s_draw_rays
{
  double ray_start_angle;
  double ray_angle_step;
  int i;
  double ray_angle;
  double ray_x;
  double ray_y;
  double step_x;
  double step_y;
  double ssssstep_x;
  double ssssstep_y;
} t_draw_rays;
#endif
