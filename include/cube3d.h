/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:01:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 13:31:01 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "Libft_plus/include/libft.h"
# include "get_next_line.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# define PI 3.141592653589
# define B_BLUE "\033[1;36m"
# define RESET "\033[0m"
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BROWN 0x8B4513
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define PURPLE 0x800080
# define BROWN 0x8B4513
# define GRAY 0xA9A9A9
# define FOV 60.0f
# define NUM_RAYS 1360
# define CAM_DIST 1360
# define MOUV_STEP 4
# define NB_TEXTURES 6
# define T1 "./textures/wood.xpm"
# define T5 "./textures/redbrick.xpm"
# define T3 "./textures/greystone.xpm"
# define T6 "./textures/bluestone.xpm"
# define T2 "./textures/mossy.xpm"
# define T4 "./textures/colorstone.xpm"
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define TEX_WIDTH 64

typedef struct s_loop
{
	float				rx;
	float				ry;
	int					xi;
	int					yi;
	int					map_x;
	int					map_y;
}						t_loop;

typedef struct s_draw_band_info
{
	int					i;
	int					x_start;
	int					band_width;
	int					draw_start;
	int					draw_end;
}						t_draw_band_info;

typedef struct s_draw_vars
{
	int					tex_x;
	int					wall_height;
	int					orientation;
	struct s_texture	*tex;
	float				dist;
	float				shade_factor;
	int					mod;
	int					x;
	int					y;
	int					tex_y;
	char				*tex_pixel;
	int					color;
	int					a;
	int					r;
	int					g;
	int					b;
}						t_draw_vars;

typedef struct s_wall_render
{
	float				fov_angle;
	int					plane;
	int					base_band;
	int					remainder;
	int					x_offset;
	int					i;
	int					band_width;
	float				dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
	t_draw_band_info	band;
}						t_wall_render;

typedef struct s_dda
{
	float				posx;
	float				posy;
	int					mapx;
	int					mapy;
	float				deltadistx;
	float				deltadisty;
	int					stepx;
	int					stepy;
	float				sidedistx;
	float				sidedisty;
	int					hit;
	int					side;
}						t_dda;

typedef struct s_draw
{
	void				*img_game;
	void				*img_map;
	char				*addr;
	char				*addr_map;
	int					bpp;
	int					bpp_map;
	int					line_len;
	int					line_len_map;
	int					endian;
	int					endian_map;
}						t_draw;

struct					s_texture
{
	void				*img;
	int					width;
	int					height;
	char				*path;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
};

typedef struct s_margin_data
{
	int					map_x1;
	int					map_x2;
	int					map_y1;
	int					map_y2;
	int					max_x;
	int					max_y;
}						t_margin_data;

struct					s_trace_line
{
	int					*tex_x;
	int					*hit_orien;
	int					orientation;
	float				step;
	float				x_cam;
	float				y_cam;
	float				x_start;
	float				y_start;
	float				x_end;
	float				y_end;
	float				x_pass;
	float				y_pass;
	float				dx;
	float				dy;
	float				dx_side;
	float				dy_side;
	int					width;
	int					height;
	float				rotation;
	float				brutdist;
	float				perpdist;
	float				*perp_tab;
	float				dx_step;
	float				dy_step;
	float				ldx;
	float				ldy;
	float				*wall_hit_x;
	float				*wall_hit_y;
	float				fov_angle;
	float				player_angle;
};

struct					s_move
{
	int					dr[4];
	int					dc[4];
};

struct					s_game_stats
{
	int					nb_start_pos;
	int					mov_count;
};

struct					s_position
{
	float				x;
	float				y;
	float				x_pixel;
	float				y_pixel;
};

struct					s_player
{
	struct s_position	pos;
};

struct					s_array
{
	struct s_draw		draw;
	struct s_game_stats	stats;
	struct s_move		move;
	struct s_texture	textures[NB_TEXTURES];
	char				*no_path;
	char				*so_path;
	char				*ea_path;
	char				*we_path;
	char				**floor;
	char				**ceiling;
	struct s_position	position;
	struct s_trace_line	ray;
	char				**line;
	char				**sorted;
	char				**map;
	int					line_len;
	int					line_len_map;
	int					is_exitable;
	int					is_newline;
	int					floor_color;
	int					ceiling_color;
};

struct					s_vars
{
	struct s_player		player;
	struct s_array		*array;
	struct s_game_stats	stats;
	struct s_trace_line	*pos;
	void				*mlx;
	void				*win;
	void				*win_map;
};

typedef struct s_point
{
	int					x;
	int					y;
	char				**tab;
}						t_point;

enum					e_keycode
{
	KEY_ARROW_UP = 65362,
	KEY_Z = 122,
	KEY_ARROW_DOWN = 115,
	KEY_S = 65364,
	KEY_ARROW_LEFT = 65361,
	KEY_Q = 113,
	KEY_ARROW_RIGHT = 65363,
	KEY_D = 100,
	KEY_SPACE = 32,
	ESC = 65307
};

/* --- MLX --- */
void					esc_close(int keycode, struct s_vars *vars);
int						default_close(struct s_vars *vars);
int						key_handler(int keycode, struct s_vars *vars);
void					init_graphics(struct s_vars *vars,
							struct s_array *array);
void					init_array_colors(struct s_array *array);

/* --- Parsing --- */
void					parse_map(struct s_vars *vars, struct s_array *array,
							struct s_game_stats *value, char *argv[]);
void					alloc_data_array(int fd, struct s_array *array,
							char *argv[]);
int						find_first_line(char **lines);
void					check_floor_and_ceilling(struct s_array *array,
							char type);
void					check_position(struct s_array *array, char pos_1,
							char pos_2);
void					check_player_start_pos(struct s_array *array,
							struct s_game_stats *value);
void					check_walls(struct s_array *array);
void					flood_fill(struct s_array *array, char **tab,
							t_point size, t_point begin);
char					**init_flood_fill(struct s_array *array,
							struct s_vars *vars, t_point *begin, t_point *size);
int						is_valid_char(char c);
void					clear_line_gnl(int fd);
int						array_len(char **array);
int						find_first_line(char **lines);
int						array_max_value(char **array);

/* --- Utils ---*/
char					**copy_array(char **source, int size);
void					handle_error_mem(struct s_array *array, char **copy);
int						open_map_file(char *argv[]);
int						ft_strchr_count(const char *s, int c);
void					free_visited(struct s_array *array);
void					free_visited_vars(struct s_vars *vars);
void					free_in_lines(struct s_array *array);
void					free_array(char **array);
void					free_array_bis(char **array);
void					free_1_array(struct s_array *array);
void					free_arrays(struct s_array *array);
void					free_tabs(struct s_vars *vars);
void					free_path(struct s_array *array);
int						get_max_width(char **array);
int						get_max_height(char **array);
void					ft_cleanup_trace_line(struct s_trace_line *pos);

/* --- Backtracking --- */
void					backtracking(struct s_array *array,
							struct s_vars *vars);
int						can_reach(struct s_array *array, int row, int col);

/* --- mapping --- */
void					mapping(struct s_array *array, struct s_vars *vars);
void					mapping_ground(struct s_array *array,
							struct s_vars *vars);
void					ground(struct s_vars *vars, int x, int y);
void					loading_player(struct s_vars *vars);
void					rotation_l(struct s_vars *vars);
void					rotation_r(struct s_vars *vars);

/* --- player_move --- */
void					move_up(struct s_vars *vars);
void					move_down(struct s_vars *vars);
void					move_right(struct s_vars *vars);
void					move_left(struct s_vars *vars);

/* --- requested_player_move --- */
void					requested_player_position_up(struct s_vars *vars);
void					requested_player_position_down(struct s_vars *vars);
void					requested_player_position_right(struct s_vars *vars);
void					requested_player_position_left(struct s_vars *vars);

/* --- draw_lines --- */
void					ft_put_pixel(int x, int y, struct s_array *array,
							int color);
void					ft_put_pixel1(int x, int y, struct s_array *array,
							int color);
void					ft_draw_grid(struct s_array *array);
void					ft_draw_line(struct s_trace_line *pos,
							struct s_array *array, struct s_position *player);
void					ft_perpendiculare(struct s_trace_line *pos,
							struct s_array *array, struct s_position *player);
void					fov(struct s_trace_line *pos, struct s_array *array,
							struct s_position *player);
void					rotate_player(struct s_trace_line *pos,
							float angle_deg);
void					ft_dda_draw_ray(struct s_position *player,
							float rayDirX, float rayDirY,
							struct s_array *array);
void					ft_draw_half_screen(struct s_array *array, int width,
							int height);

/*--- ray_casting ---*/
void					draw_walls(struct s_trace_line *pos,
							struct s_array *array);
void					ft_init_line(struct s_trace_line *pos,
							struct s_array *array, struct s_position *player);
void					ft_init_line2(struct s_trace_line *pos,
							struct s_position *player, float x, float y);
void					ft_init_line1(struct s_trace_line *pos,
							struct s_position *player, float x, float y);
void					loop(struct s_trace_line *pos, struct s_array *array,
							struct s_position *player);

/*---gameplay---*/
void					check_characters_in_map(struct s_array *array);
void					distance(struct s_array *array,
							struct s_position *player, int i);

/*---game_loop---*/
void					ft_game_loop(struct s_vars *vars,
							struct s_array *array);
/*---margin---*/
int						check_margin(float x, float y, char **map, int margin);
/*---render_frame---*/
void					clear_image(struct s_array *array, int width,
							int height);
void					render_frame(struct s_vars *vars);
/*---band_utils---*/
void					ft_init_var(t_draw_vars *var, t_draw_band_info band,
							struct s_trace_line *pos, struct s_array *array);
void					ft_init_render(t_wall_render *r, struct s_array *array);
/*---utils1.c---*/
char					**copy_array(char **source, int size);
int						get_max_width(char **array);
int						get_max_height(char **array);
void					free_tabs(struct s_vars *vars);
void					free_array(char **array);
#endif
