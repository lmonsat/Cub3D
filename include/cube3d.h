/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:01:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/14 15:56:26 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "Libft_plus/include/libft.h"
# include "get_next_line.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <fcntl.h> // open, O_CREAT, O_RDONLY
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# define PI 3.141592653589
# define B_BLUE "\033[1;36m"
# define RESET "\033[0m"
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define PURPLE 0x800080

# define FOV 60.0f         // Champ de vision en degrés
# define NUM_RAYS 120      // Nombre de rayons à lancer
# define STEP (FOV / NUM_RAYS)
# define DEG2RAD(x) ((x) * PI / 180.0f)

//structure utile pour la fonction put_pixel
struct					s_draw
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		endian;
};

struct	s_trace_line
{
	int x_start; //depart x (joueur)
	int y_start; //depart y (joueur)
	int x_end;   //fin du ray (mur)
	int y_end;	// fin du ray (mur)
	int dx; //x_end - x_start
	int dy; //y_end - y_start
	int width; //array->elmt.cols * 40
	int height; //array->elmt.rows
	float rotation; //for rotation of fov
	int xfov_s; //depart fov x
	int yfov_s; //depart fov y
	int xfov_e; //fin fov x
	int yfov_e; //fin fov y
};

struct					s_first
{
	int					cols;
	int					first_line_nb_char;
	int					rows;
};

struct					s_move
{
	int					dr[4];
	int					dc[4];
};

struct					s_game_stats
{
	int					nb_exit;
	int					nb_player;
	int					nb_collectibles;
	int					collected;
	int					mov_count;
};

struct					s_position
{
	int					x;
	int					y;
	int					x_pixel;
	int					y_pixel;
};

struct					s_player
{
	struct s_position	pos;
	int					collected;
};

struct					s_array
{
	struct s_draw		draw;
	struct s_game_stats	stats;
	struct s_first		elmt;
	struct s_move		move;
	struct s_position   position;
	struct s_trace_line ray;
	int					**visited;
	char				**line;
	char				**backtracking;
	int					line_len;
	int					is_exitable;
	int					is_newline;
};

struct					s_vars
{
	struct s_player		player;
	struct s_array		*array;
	struct s_game_stats	stats;
	void				*mlx;
	void				*win;

};

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
void    esc_close(int keycode, struct s_vars *vars);
int default_close(struct s_vars *vars);
int key_handler(int keycode, struct s_vars *vars);

/* --- Parsing --- */
void	parse_map(struct s_vars *vars, struct s_array *array, struct s_game_stats *value, char *argv[]);

/* --- Utils ---*/
char	**copy_array(char **source, struct s_array *array);
void	handle_error_mem(struct s_array *array, char **copy);
int	open_map_file(char *argv[]);
int	ft_strchr_count(const char *s, int c);
void	free_visited(struct s_array *array);
void	free_visited_vars(struct s_vars *vars);
void	free_in_lines(struct s_array *array);
void	free_1_array(struct s_array *array);
void	free_arrays(struct s_array *array);
void	free_tabs(struct s_vars *vars);

/* --- Backtracking --- */
void	backtracking(struct s_array *array, struct s_vars *vars);
int	can_reach(struct s_array *array, int row, int col);

/* --- mapping --- */
void	mapping(struct s_array *array, struct s_vars *vars);
void	mapping_ground(struct s_array *array, struct s_vars *vars);
void	ground(struct s_vars *vars, int x, int y);
void	loading_player(struct s_vars *vars);

/* --- player_move --- */
void	move_up(struct s_vars *vars, int x, int y);
void	move_down(struct s_vars *vars, int x, int y);
void	move_right(struct s_vars *vars, int x, int y);
void	move_left(struct s_vars *vars, int x, int y);
void	clear_image(struct s_array *array, int width, int height);

/* --- requested_player_move --- */
void	requested_player_position_up(struct s_vars *vars);
void	requested_player_position_down(struct s_vars *vars);
void	requested_player_position_right(struct s_vars *vars);
void	requested_player_position_left(struct s_vars *vars);

/* --- draw_lines --- */
void ft_put_pixel(int x, int y, struct s_array *array, int color);
void ft_draw_grid(struct s_array *array/*, struct s_vars *vars*/);
//void ft_draw_line(struct s_trace_line *pos, struct s_array *array, /*struct s_vars *vars,*/ struct s_position *player);
void ft_draw_line(struct s_trace_line *pos, struct s_array *array, float angle_deg, struct s_position *player);
void draw_fov(struct s_vars *vars);
void draw_fov_360(struct s_vars *vars);
//void ft_draw_ray(struct s_trace_line *pos, struct s_array *array, struct s_position *player, float angle);
//void ft_draw_all_rays(struct s_trace_line *pos, struct s_array *array, struct s_vars *vars, struct s_position *player);
//void ft_draw_multiple_rays(struct s_array *array, struct s_vars *vars);
//void ft_draw_cone(struct s_array *array, struct s_vars *vars, struct s_position *player);
#endif
