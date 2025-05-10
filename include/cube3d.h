/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:01:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/07 17:15:30 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "Libft_plus/include/libft.h"
# include "get_next_line.h"
# include "mlx_linux/mlx.h"
# include "mlx_linux/mlx_int.h"
# include <errno.h>
# include <fcntl.h> // open, O_CREAT, O_RDONLY
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
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define ORANGE 0xFFA500
# define PINK 0xFFC0CB
# define PURPLE 0x800080
# define BROWN 0x8B4513
# define GRAY 0xA9A9A9
# define FOV 60.0f         // Champ de vision en degrés
# define NUM_RAYS 1360      // Nombre de rayons à lancer
# define cam_dist 1360		//distance entre le joueur et le plan camera
# define STEP (FOV / NUM_RAYS)
# define DEG2RAD(x) ((x) * PI / 180.0f)
# define mouv_step 4

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
	float step;
	float x_cam;
	float y_cam;
	float x_start; //depart x (joueur)
	float y_start; //depart y (joueur)
	float x_end;   //fin du ray (mur)
	float y_end;	// fin du ray (mur)
	float x_pass;   //point de passage x
	float y_pass;   //point de passage y
	float dx; //x_end - x_start vecteur de direction avant arriere
	float dy; //y_end - y_start vecteur de direction avant arriere
	float dx_side; //vecteur de direction gauche droite
	float dy_side; //vecteur de direction gauche droite
	int width;
	int height; 
	float rotation; //for rotation of fov
	float brutdist; //distance brut
	float perpdist; //distance corriger pour effet fisheye
	float *perp_tab;
	float dx_step;
	float dy_step;
	float ldx;
	float ldy;
};

/*struct s_measure
{
	//coordonnées du joueur par case
	int mapx;
	int mapy;

	//distance que le rayon doit parcourir pour traverser une case
	float deltaDistx;
	float deltaDisty;

	//variable de direction
	int stepx;
	int stepy;
	float sidedistx;
	float sidedisty;

	float distance;
	int hit;
	int side // 0 collision en x 1 collision en y
};*/

struct					s_first
{

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
	float					x;
	float					y;
	float					x_pixel;
	float					y_pixel;
};

struct					s_player
{
	struct s_position	pos;
};

struct					s_array
{
	struct s_draw		draw;
	struct s_game_stats	stats;
	struct s_first		elmt;
	struct s_move		move;
	char				*NO_path;
	char				*SO_path;
	char				*EA_path;
	char				*WE_path;
	char				**floor;
	char				**ceiling;
	struct s_position   position;
	struct s_trace_line ray;
	char				**line;
	int					line_len;
	int					is_exitable;
	int					is_newline;
};

struct					s_vars
{
	struct s_player		player;
	struct s_array		*array;
	struct s_game_stats	stats;
	struct s_trace_line	*pos;
	void				*mlx;
	void				*win;

};

typedef struct  s_point
{
int           x;
int           y;
}               t_point;

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
int		open_map_file(char *argv[]);
int		ft_strchr_count(const char *s, int c);
void	free_visited(struct s_array *array);
void	free_visited_vars(struct s_vars *vars);
void	free_in_lines(struct s_array *array);
void	free_array(char **array);
void	free_1_array(struct s_array *array);
void	free_arrays(struct s_array *array);
void	free_tabs(struct s_vars *vars);
void free_path(struct s_array *array);
int get_max_width(char **array);
int get_max_height(char **array);

/* --- Backtracking --- */
void	backtracking(struct s_array *array, struct s_vars *vars);
int	can_reach(struct s_array *array, int row, int col);

/* --- mapping --- */
void	mapping(struct s_array *array, struct s_vars *vars);
void	mapping_ground(struct s_array *array, struct s_vars *vars);
void	ground(struct s_vars *vars, int x, int y);
void	loading_player(struct s_vars *vars);

/* --- player_move --- */
void	clear_image(struct s_array *array, int width, int height);
void	render_frame(struct s_vars *vars);

/* --- requested_player_move --- */
void	requested_player_position_up(struct s_vars *vars);
void	requested_player_position_down(struct s_vars *vars);
void	requested_player_position_right(struct s_vars *vars);
void	requested_player_position_left(struct s_vars *vars);

/* --- draw_lines --- */
void ft_put_pixel(int x, int y, struct s_array *array, int color);
void ft_draw_grid(struct s_array *array);
void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void ft_perpendiculare(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void rotate_player(struct s_trace_line *pos, float angle_deg);
void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array);

/*--- ray_casting ---*/
void draw_walls(struct s_trace_line *pos, struct s_array *array);
void ft_init_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void ft_init_line2(struct s_trace_line *pos, struct s_position *player, float x, float y);
void ft_init_line1(struct s_trace_line *pos, struct s_position *player, float x, float y);
void loop(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
#endif
