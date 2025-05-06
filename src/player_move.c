/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/06 15:42:03 by lmonsat          ###   ########.fr       */
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
			ft_put_pixel(x, y, array, BLACK);
			x++;
		}
		y++;
	}
}

void debug_fov(float *ray_distances, int count)
{
    printf("=== DEBUG RAY DISTANCES ===\n");
    for (int i = 0; i < count; i++)
    {
        printf("Ray %2d: %.2f\n", i, ray_distances[i]);
    }
    printf("===========================\n");
}

void	render_frame(struct s_vars *vars)
{
	clear_image(vars->array, vars->array->ray.width, vars->array->ray.height); // Efface tout avant de redessiner
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	ft_draw_grid(vars->array);
	ft_draw_line(&vars->array->ray, vars->array, &vars->player.pos);
	fov(&vars->array->ray, vars->array, &vars->player.pos);
	draw_walls(&vars->array->ray, vars->array);
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
