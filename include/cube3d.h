/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:01:21 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/02 15:45:38 by lmonsat          ###   ########.fr       */
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
# define B_BLUE "\033[1;36m"
# define RESET "\033[0m"

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
	struct s_game_stats	stats;
	struct s_first		elmt;
	struct s_move		move;
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

#endif
