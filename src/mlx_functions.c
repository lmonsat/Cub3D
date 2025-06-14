/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:00:23 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/14 21:51:23 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	free_line(struct s_trace_line *pos)
{
	if (pos->perp_tab)
	{
		free(pos->perp_tab);
		pos->perp_tab = NULL;
	}
	if (pos->hit_orien)
	{
		free(pos->hit_orien);
		pos->hit_orien = NULL;
	}
	if (pos->tex_x)
	{
		free(pos->tex_x);
		pos->tex_x = NULL;
	}
}

void	free_textures(void *mlx, struct s_texture *textures)
{
	int	i;

	i = 0;
	while (i < NB_TEXTURES)
	{
		if (textures[i].img)
		{
			mlx_destroy_image(mlx, textures[i].img);
			textures[i].img = NULL;
		}
		i++;
	}
}

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
		free_textures(vars->mlx, vars->array->textures);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win_map);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		ft_cleanup_trace_line(&vars->array->ray);
		free_array(vars->array->map);
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
	free_textures(vars->mlx, vars->array->textures);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win_map);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	ft_cleanup_trace_line(&vars->array->ray);
	free_array(vars->array->map);
	free_array(vars->array->ceiling);
	free_array(vars->array->floor);
	free_path(vars->array);
	exit(0);
	return (0);
}

static void	rotation_l(struct s_vars *vars)
{
	vars->array->ray.rotation -= 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0,
		0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map,
		0, 0);
}

static void	rotation_r(struct s_vars *vars)
{
	vars->array->ray.rotation += 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0,
		0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map,
		0, 0);
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
	else if (keycode == KEY_ARROW_LEFT)
		rotation_l(vars);
	else if (keycode == KEY_ARROW_RIGHT)
		rotation_r(vars);
	else if (keycode == ESC)
	{
		esc_close(keycode, vars);
		exit(0);
	}
	return (0);
}
