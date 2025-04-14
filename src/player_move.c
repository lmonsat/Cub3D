/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/14 14:25:32 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	move_up(struct s_vars *vars, int x, int y)
{
	vars->player.pos.y -= 1;
	vars->player.pos.y_pixel -= 40;
	vars->stats.mov_count++;
	//printf("Movement count : %d\n", vars->stats.mov_count);
	//ground(vars, x * 40, y * 40);
	ft_draw_grid(vars->array, vars);
	ft_draw_line(&vars->array->ray, vars->array, vars, &vars->player.pos);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
}

void	move_down(struct s_vars *vars, int x, int y)
{
	vars->player.pos.y += 1;
	vars->player.pos.y_pixel += 40;
	vars->stats.mov_count++;
	//printf("Movement count : %d\n", vars->stats.mov_count);
	//ground(vars, x * 40, y * 40);
	ft_draw_grid(vars->array, vars);
	ft_draw_line(&vars->array->ray, vars->array, vars, &vars->player.pos);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
}

void	move_right(struct s_vars *vars, int x, int y)
{
	vars->player.pos.x += 1;
	vars->player.pos.x_pixel += 40;
	vars->stats.mov_count++;
	printf("Movement count : %d\n", vars->stats.mov_count);
	//ground(vars, x * 40, y * 40);
	ft_draw_grid(vars->array, vars);
	ft_draw_line(&vars->array->ray, vars->array, vars, &vars->player.pos);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
}

void	move_left(struct s_vars *vars, int x, int y)
{
	vars->player.pos.x -= 1;
	vars->player.pos.x_pixel -= 40;
	vars->stats.mov_count++;
	printf("Movement count : %d\n", vars->stats.mov_count);
	//ground(vars, x * 40, y * 40);
	ft_draw_grid(vars->array, vars);
	ft_draw_line(&vars->array->ray, vars->array, vars, &vars->player.pos);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
}
