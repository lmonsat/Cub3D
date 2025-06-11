/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:01:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/11 16:02:24 by drenquin         ###   ########.fr       */
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
# define BROWN 0x8B4513
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
# define NB_TEXTURES 6
# define T1 "./textures/wood.xpm"
# define T5 "./textures/redbrick.xpm"
# define T3 "./textures/greystone.xpm"
# define T6 "./textures/bluestone.xpm"
# define T2 "./textures/mossy.xpm"
# define T4 "./textures/colorstone.xpm"
# define NORTH 0
# define SOUTH 1
# define EAST  2
# define WEST  3
# define tex_width 64

//structure utile pour la fonction put_pixel
typedef struct s_draw
{
	void	*img_game;
	void	*img_map;
	char	*addr;
	char	*addr_map;
	int		bpp;
	int		bpp_map;
	int		line_len;
	int		line_len_map;
	int		endian;
	int		endian_map;
} t_draw;

struct			s_texture
{
    void    *img;
    int     width;
    int     height;
	char 	*path;
	char	*addr;
    int     bpp;
    int     line_len;
    int     endian;
};

struct	s_trace_line
{
	int *tex_x;
	int *hit_orien;
	int orientation; // 0 = NORD, 1 = SUD, 2 = EST, 3 = OUEST
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
	float *wall_hit_x;
	float *wall_hit_y;
	float fov_angle;
	float player_angle;
};

/*struct					s_first
{

};*/

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
	//struct s_first		elmt;
	struct s_move		move;
	struct s_texture    textures[NB_TEXTURES];
	const char				*NO_path;
	const char				*SO_path;
	const char				*EA_path;
	const char				*WE_path;
	char				**floor;
	char				**ceiling;
	struct s_position   position;
	struct s_trace_line ray;
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
int 	find_first_line(char **lines);

/* --- Utils ---*/
char	**copy_array(char **source, int size);
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
void ft_cleanup_trace_line(struct s_trace_line *pos);

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
void	move_up(struct s_vars *vars);
void	move_down(struct s_vars *vars);
void	move_right(struct s_vars *vars);
void	move_left(struct s_vars *vars);

/* --- requested_player_move --- */
void	requested_player_position_up(struct s_vars *vars);
void	requested_player_position_down(struct s_vars *vars);
void	requested_player_position_right(struct s_vars *vars);
void	requested_player_position_left(struct s_vars *vars);

/* --- draw_lines --- */
//void ft_put_pixel(int x, int y, struct s_array *array, int color, int is_minimap);
void ft_put_pixel(int x, int y, struct s_array *array, int color);
void ft_put_pixel1(int x, int y, struct s_array *array, int color);
void ft_draw_grid(struct s_array *array);
void ft_draw_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void ft_perpendiculare(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void rotate_player(struct s_trace_line *pos, float angle_deg);
void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array);
void ft_draw_half_screen(struct s_array *array, int width, int height);

/*--- ray_casting ---*/
void draw_walls(struct s_trace_line *pos, struct s_array *array);
//void draw_walls(struct s_trace_line *pos, struct s_array *array, struct s_texture *textures);
void ft_init_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
void ft_init_line2(struct s_trace_line *pos, struct s_position *player, float x, float y);
void ft_init_line1(struct s_trace_line *pos, struct s_position *player, float x, float y);
void loop(struct s_trace_line *pos, struct s_array *array, struct s_position *player);
#endif
