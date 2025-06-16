/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 19:14:28 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	move_up(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	if (!vars || !vars->array)
		return ;
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	next_x = vars->player.pos.x_pixel + vars->array->ray.dx * mouv_step;
	next_y = vars->player.pos.y_pixel + vars->array->ray.dy * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	move_down(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	if (!vars || !vars->array)
		return ;
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	next_x = vars->player.pos.x_pixel - vars->array->ray.dx * mouv_step;
	next_y = vars->player.pos.y_pixel - vars->array->ray.dy * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	move_right(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	if (!vars || !vars->array)
		return ;
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	next_x = vars->player.pos.x_pixel + vars->array->ray.dx_side * mouv_step;
	next_y = vars->player.pos.y_pixel + vars->array->ray.dy_side * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	move_left(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	if (!vars || !vars->array)
		return ;
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	next_x = vars->player.pos.x_pixel - vars->array->ray.dx_side * mouv_step;
	next_y = vars->player.pos.y_pixel - vars->array->ray.dy_side * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}

void	clear_image(struct s_array *array, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_put_pixel1(x, y, array, BLACK);
			x++;
		}
		y++;
	}
}

void	render_frame(struct s_vars *vars)
{
	clear_image(vars->array, vars->array->ray.width, vars->array->ray.height);
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	ft_draw_grid(vars->array);
	ft_draw_line(&vars->array->ray, vars->array, &vars->player.pos);
	fov(&vars->array->ray, vars->array, &vars->player.pos);
	ft_draw_half_screen(vars->array, vars->array->ray.width,
		vars->array->ray.height);
	draw_walls(&vars->array->ray, vars->array);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0,
		0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map,
		0, 0);
}
