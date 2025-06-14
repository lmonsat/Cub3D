/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/14 23:09:09 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_init_margin(t_margin_data *d, char **map)
{
	d->max_y = 0;
	d->max_x = 0;
	while (map[d->max_y])
		d->max_y++;
	while (map[0][d->max_x])
		d->max_x++;
}

void	ft_init_margin1(t_margin_data *d, float x, float y, int margin)
{
	d->map_x1 = (int)(x + margin) / 40;
	d->map_x2 = (int)(x - margin) / 40;
	d->map_y1 = (int)(y + margin) / 40;
	d->map_y2 = (int)(y - margin) / 40;
}

int	check_margin(float x, float y, char **map, int margin)
{
	t_margin_data	d;

	if (!map || !map[0])
	{
		printf("Erreur : map ou map[0] non initialisé\n");
		exit(1);
	}
	ft_init_margin(&d, map);
	ft_init_margin1(&d, x, y, margin);
	if (d.map_x1 < 0 || d.map_x1 >= d.max_x || d.map_x2 < 0
		|| d.map_x2 >= d.max_x || d.map_y1 < 0 || d.map_y1 >= d.max_y
		|| d.map_y2 < 0 || d.map_y2 >= d.max_y)
		return (0);
	if (!map[d.map_y1] || !map[d.map_y2])
		return (0);
	if (map[d.map_y1][d.map_x1] == '1' || map[d.map_y1][d.map_x2] == '1'
		|| map[d.map_y2][d.map_x1] == '1' || map[d.map_y2][d.map_x2] == '1')
		return (0);
	return (1);
}

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
