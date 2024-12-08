#ifndef STRUCTS_HELPER_H
# define STRUCTS_HELPER_H

typedef struct s_draw_map
{
  float start_angle;
  float angle_step;
  float p_x;
  float p_y;
  float ray_angle;
  float ray_x;
  float ray_y;
  float dist_x;
  float dist_y;
  int map_x;
  int map_y;
  int step_x;
  int step_y;
  float side_dist_y;
  float side_dist_x;
  int i;
} t_draw_map;

typedef struct s_draw_rays
{
  float ray_start_angle;
  float ray_angle_step;
  int i;
  float ray_angle;
  float ray_x;
  float ray_y;
  float step_x;
  float step_y;
  float ssssstep_x;
  float ssssstep_y;
} t_draw_rays;
#endif
