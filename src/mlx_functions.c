/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:00:23 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/01 20:00:50 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	esc_close(int keycode, struct s_vars *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_tabs(vars);
		free_visited_vars(vars);
		exit(0);
	}
}

int	default_close(struct s_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_tabs(vars);
	free_visited_vars(vars);
	exit(0);
	return (0);
}

int	key_handler(int keycode, struct s_vars *vars)
{
	if (keycode == KEY_ARROW_UP || keycode == KEY_Z)
	{
		requested_player_position_up(vars);
	}
	else if (keycode == KEY_ARROW_DOWN || keycode == KEY_S)
	{
		requested_player_position_down(vars);
	}
	else if (keycode == KEY_ARROW_RIGHT || keycode == KEY_D)
	{
		requested_player_position_right(vars);
	}
	else if (keycode == KEY_ARROW_LEFT || keycode == KEY_Q)
	{
		requested_player_position_left(vars);
	}
	else if (keycode == ESC)
	{
		esc_close(keycode, vars);
		exit(0);
	}
	return (0);
}