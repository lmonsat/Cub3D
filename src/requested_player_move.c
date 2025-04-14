/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requested_player_move.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:53:27 by lmonsat           #+#    #+#             */
/*   Updated: 2024/06/17 15:42:21 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	requested_player_position_up(struct s_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.pos.x;
	y = vars->player.pos.y - 1;
	if (vars->array->line[y][x] == '0' || vars->array->line[y][x] == 'P')
		move_up(vars, x, y);
	else if (vars->array->line[y][x] == '1')
		return ;
	else if (vars->array->line[y][x] == 'C')
	{
		move_up(vars, x, y);
		vars->player.collected++;
	}
	else if (vars->array->line[y][x] == 'E')
	{
		if (vars->player.collected == vars->stats.nb_collectibles)
		{
			move_up(vars, x, y);
			mlx_loop_end(vars->mlx);
		}
		return ;
	}
	//ground(vars, x * 40, (y + 1) * 40);
}

void	requested_player_position_down(struct s_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.pos.x;
	y = vars->player.pos.y + 1;
	if (vars->array->line[y][x] == '0' || vars->array->line[y][x] == 'P')
		move_down(vars, x, y);
	else if (vars->array->line[y][x] == '1')
		return ;
	else if (vars->array->line[y][x] == 'C')
	{
		move_down(vars, x, y);
		vars->player.collected++;
	}
	else if (vars->array->line[y][x] == 'E')
	{
		if (vars->player.collected == vars->stats.nb_collectibles)
		{
			move_down(vars, x, y);
			mlx_loop_end(vars->mlx);
		}
		return ;
	}
	//ground(vars, x * 40, (y - 1) * 40);
}

void	requested_player_position_right(struct s_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.pos.x + 1;
	y = vars->player.pos.y;
	if (vars->array->line[y][x] == '0' || vars->array->line[y][x] == 'P')
		move_right(vars, x, y);
	else if (vars->array->line[y][x] == '1')
		return ;
	else if (vars->array->line[y][x] == 'C')
	{
		move_right(vars, x, y);
		vars->player.collected++;
	}
	else if (vars->array->line[y][x] == 'E')
	{
		if (vars->player.collected == vars->stats.nb_collectibles)
		{
			move_right(vars, x, y);
			mlx_loop_end(vars->mlx);
		}
		return ;
	}
	//ground(vars, (x - 1) * 40, y * 40);
}

void	requested_player_position_left(struct s_vars *vars)
{
	int	x;
	int	y;

	x = vars->player.pos.x - 1;
	y = vars->player.pos.y;
	if (vars->array->line[y][x] == '0' || vars->array->line[y][x] == 'P')
		move_left(vars, x, y);
	else if (vars->array->line[y][x] == '1')
		return ;
	else if (vars->array->line[y][x] == 'C')
	{
		move_left(vars, x, y);
		vars->player.collected++;
	}
	else if (vars->array->line[y][x] == 'E')
	{
		if (vars->player.collected == vars->stats.nb_collectibles)
		{
			move_left(vars, x, y);
			mlx_loop_end(vars->mlx);
		}
		return ;
	}
	//ground(vars, (x + 1) * 40, y * 40);
}
