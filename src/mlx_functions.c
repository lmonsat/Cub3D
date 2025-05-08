/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:00:23 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/07 19:25:26 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	esc_close(int keycode, struct s_vars *vars)
{
	if (keycode == 65307)
	{
		if (vars->mlx && vars->array->draw.img_game)
		{
			mlx_destroy_image(vars->mlx, vars->array->draw.img_game);
			vars->array->draw.img_game = NULL;
		}
		if (vars->mlx && vars->array->draw.img_map)
		{
			mlx_destroy_image(vars->mlx, vars->array->draw.img_map);
			vars->array->draw.img_map = NULL;
		}
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win_map);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_array(vars->array->line);
		free_array(vars->array->ceiling);
		free_array(vars->array->floor);
		free_path(vars->array);
		exit(0);
	}
}

int	default_close(struct s_vars *vars)
{
	if (vars->mlx && vars->array->draw.img_game)
	{
		mlx_destroy_image(vars->mlx, vars->array->draw.img_game);
		vars->array->draw.img_game = NULL;
	}
	if (vars->mlx && vars->array->draw.img_map)
	{
		mlx_destroy_image(vars->mlx, vars->array->draw.img_map);
		vars->array->draw.img_map = NULL;
	}
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win_map);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_array(vars->array->line);
	free_array(vars->array->ceiling);
	free_array(vars->array->floor);
	free_path(vars->array);
	exit(0);
	return (0);
}

void rotation_l(struct s_vars *vars)
{
	//int	width = vars->array->elmt.cols * 40;
	//int	height = vars->array->elmt.rows * 40;
	
	//clear_image(vars->array, width, height); // Efface tout avant de redessiner
	//ft_draw_grid(vars->array);
	vars->array->ray.rotation += 5;
	//draw_fov(vars);
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

void rotation_r(struct s_vars *vars)
{
	//int	width = vars->array->elmt.cols * 40;
	//int	height = vars->array->elmt.rows * 40;
	
	//clear_image(vars->array, width, height); // Efface tout avant de redessiner
	//ft_draw_grid(vars->array);
	vars->array->ray.rotation -= 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

int	key_handler(int keycode, struct s_vars *vars)
{
	if (keycode == KEY_ARROW_UP || keycode == KEY_Z)
		requested_player_position_up(vars);
	else if (keycode == KEY_ARROW_DOWN || keycode == KEY_S)
		requested_player_position_down(vars);
	else if (keycode == KEY_D)
		requested_player_position_right(vars);
	else if (keycode == KEY_Q)
		requested_player_position_left(vars);
	else if(keycode == KEY_ARROW_LEFT)
		rotation_l(vars);
	else if(keycode == KEY_ARROW_RIGHT)
		rotation_r(vars);
	else if (keycode == ESC)
	{
		esc_close(keycode, vars);
		exit(0);
	}
	return (0);
}
