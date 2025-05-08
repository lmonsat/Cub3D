/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:00:23 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/07 18:16:10 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	esc_close(int keycode, struct s_vars *vars)
{
	if (keycode == 65307)
	{
		if (vars->mlx && vars->array->draw.img_ptr)
		{
			mlx_destroy_image(vars->mlx, vars->array->draw.img_ptr);
			vars->array->draw.img_ptr = NULL;
		}
		mlx_destroy_window(vars->mlx, vars->win);
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
	mlx_destroy_window(vars->mlx, vars->win);
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
	vars->array->ray.rotation += 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

void rotation_r(struct s_vars *vars)
{
	vars->array->ray.rotation -= 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

void	move_up(struct s_vars *vars)
{
	//vars->player.pos.y_pixel -= 4;
	vars->player.pos.x_pixel += vars->array->ray.dx * mouv_step;
    vars->player.pos.y_pixel += vars->array->ray.dy * mouv_step;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

void	move_down(struct s_vars *vars)
{
	//vars->player.pos.y_pixel += 4;
	vars->player.pos.x_pixel -= vars->array->ray.dx * mouv_step;
    vars->player.pos.y_pixel -= vars->array->ray.dy * mouv_step;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

void	move_right(struct s_vars *vars)
{
	//vars->player.pos.x_pixel += 4;
	vars->player.pos.x_pixel += vars->array->ray.dx_side * mouv_step;
    vars->player.pos.y_pixel += vars->array->ray.dy_side * mouv_step;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

void move_left(struct s_vars *vars)
{
	//vars->player.pos.x_pixel -= 4;
	vars->player.pos.x_pixel -= vars->array->ray.dx_side * mouv_step;
    vars->player.pos.y_pixel -= vars->array->ray.dy_side * mouv_step;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}

int	key_handler(int keycode, struct s_vars *vars)
{
	if (keycode == KEY_ARROW_UP || keycode == KEY_Z)
		move_up(vars);
	else if (keycode == KEY_ARROW_DOWN || keycode == KEY_S)
		move_down(vars);
	else if (keycode == KEY_D)
		move_right(vars);
	else if (keycode == KEY_Q)
		move_left(vars);
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
