/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 20:00:23 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/03 23:23:44 by drenquin         ###   ########.fr       */
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
		if (vars->mlx && vars->array->draw.img_ptr)
		{
			mlx_destroy_image(vars->mlx, vars->array->draw.img_ptr);
			vars->array->draw.img_ptr = NULL;
		}
		free_textures(vars->mlx, vars->array->textures);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_line(&vars->array->ray);
		free_array(vars->array->line);
		free_array(vars->array->ceiling);
		free_array(vars->array->floor);
		free_path(vars->array);
		exit(0);
	}
}

int	default_close(struct s_vars *vars)
{
	if (vars->mlx && vars->array->draw.img_ptr)
	{
		mlx_destroy_image(vars->mlx, vars->array->draw.img_ptr);
		vars->array->draw.img_ptr = NULL;
	}
	free_textures(vars->mlx, vars->array->textures);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	//free_line(&vars->array->ray);
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

int		check_margin(float x, float y, char **map, int margin)
{
	int map_x1;
	int map_x2;
	int map_y1;
	int map_y2;

	map_x1 = (int)(x + margin) / 40;
	map_x2 = (int)(x + margin) / 40;
	map_y1 = (int)(y + margin) / 40;
	map_y2 = (int)(y - margin) / 40;

	if (map[map_y1][map_x1] == '1' || map[map_y1][map_x2] == '1' ||
		map[map_y2][map_x1] == '1' || map[map_y2][map_x2] == '1')
		return(0);
	return(1);
}

void	move_up(struct s_vars *vars)
{
	float next_x;
	float next_y;
	int map_x;
	int map_y;

	next_x = vars->player.pos.x_pixel + vars->array->ray.dx * mouv_step;
	next_y =  vars->player.pos.y_pixel + vars->array->ray.dy * mouv_step;
	map_x = (int)(next_x) / 40;
	map_y = (int)(next_y) / 40;
	if (check_margin(next_x, next_y, vars->array->line, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	move_down(struct s_vars *vars)
{
	float next_x;
	float next_y;
	int map_x;
	int map_y;

	next_x = vars->player.pos.x_pixel - vars->array->ray.dx * mouv_step;
    next_y = vars->player.pos.y_pixel - vars->array->ray.dy * mouv_step;
	map_x = (int)(next_x) / 40;
	map_y = (int)(next_y) / 40;
	if (check_margin(next_x, next_y, vars->array->line, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	move_right(struct s_vars *vars)
{
	float next_x;
	float next_y;
	int map_x;
	int map_y;

	next_x = vars->player.pos.x_pixel - vars->array->ray.dx_side * mouv_step;
    next_y = vars->player.pos.y_pixel - vars->array->ray.dy_side * mouv_step;
	map_x = (int)(next_x) / 40;
	map_y = (int)(next_y) / 40;
	if (check_margin(next_x, next_y, vars->array->line, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void move_left(struct s_vars *vars)
{
	float next_x;
	float next_y;
	int map_x;
	int map_y;

	next_x = vars->player.pos.x_pixel + vars->array->ray.dx_side * mouv_step;
    next_y = vars->player.pos.y_pixel + vars->array->ray.dy_side * mouv_step;
	map_x = (int)(next_x) / 40;
	map_y = (int)(next_y) / 40;
	if (check_margin(next_x, next_y, vars->array->line, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
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
