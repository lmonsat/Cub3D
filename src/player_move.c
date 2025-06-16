/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 23:04:20 by drenquin         ###   ########.fr       */
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
	next_x = vars->player.pos.x_pixel + vars->array->ray.dx * MOUV_STEP;
	next_y = vars->player.pos.y_pixel + vars->array->ray.dy * MOUV_STEP;
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
	next_x = vars->player.pos.x_pixel - vars->array->ray.dx * MOUV_STEP;
	next_y = vars->player.pos.y_pixel - vars->array->ray.dy * MOUV_STEP;
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
	next_x = vars->player.pos.x_pixel + vars->array->ray.dx_side * MOUV_STEP;
	next_y = vars->player.pos.y_pixel + vars->array->ray.dy_side * MOUV_STEP;
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
	next_x = vars->player.pos.x_pixel - vars->array->ray.dx_side * MOUV_STEP;
	next_y = vars->player.pos.y_pixel - vars->array->ray.dy_side * MOUV_STEP;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x_pixel = next_x;
		vars->player.pos.y_pixel = next_y;
	}
	render_frame(vars);
}
