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

void	clear_image(struct s_array *array, int width, int height)
{
	int	x, y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			// On remplit l'image en noir
			//*(int *)(array->draw->addr + (y * draw->line_len + x * (draw->bpp / 8))) = 0x000000;
			ft_put_pixel(x, y, array, BLACK);
			x++;
		}
		y++;
	}
}

void	render_frame(struct s_vars *vars)
{
	int	width = vars->array->elmt.cols * 40;
	int	height = vars->array->elmt.rows * 40;

	clear_image(vars->array, width, height); // Efface tout avant de redessiner

	ft_draw_grid(vars->array);
	ft_draw_line(&vars->array->ray, vars->array, &vars->player.pos);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_ptr, 0, 0);
}



void	move_up(struct s_vars *vars, int x, int y)
{
	vars->player.pos.y -= 1;
	vars->player.pos.y_pixel -= 40;
	vars->stats.mov_count++;
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
	render_frame(vars);
}

void	move_down(struct s_vars *vars, int x, int y)
{
	vars->player.pos.y += 1;
	vars->player.pos.y_pixel += 40;
	vars->stats.mov_count++;
	printf("Movement count : %d\n", vars->stats.mov_count);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
	render_frame(vars);

}

void	move_right(struct s_vars *vars, int x, int y)
{
	vars->player.pos.x += 1;
	vars->player.pos.x_pixel += 40;
	vars->stats.mov_count++;
	printf("Movement count : %d\n", vars->stats.mov_count);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
	render_frame(vars);
}

void	move_left(struct s_vars *vars, int x, int y)
{
	vars->player.pos.x -= 1;
	vars->player.pos.x_pixel -= 40;
	vars->stats.mov_count++;
	printf("Movement count : %d\n", vars->stats.mov_count);
	if (vars->array->line[y][x] == 'C')
	{
		vars->array->line[y][x] = '0';
	}
	render_frame(vars);
}
