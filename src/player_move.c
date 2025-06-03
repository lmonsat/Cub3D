/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:52:11 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/04 01:23:27 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int		check_margin(float x, float y, char **map, int margin)
{
	int map_x1 = (int)(x + margin);
	int map_x2 = (int)(x - margin);
	int map_y1 = (int)(y + margin);
	int map_y2 = (int)(y - margin);

	printf("mapx1: %d\n", map_x1);
	printf("mapx2: %d\n", map_x2);
	printf("mapy1: %d\n", map_y1);
	printf("mapy2: %d\n", map_y2);

	if (!map || !map[0]) 
	{
		printf("Erreur : map ou map[0] non initialisé\n");
		exit(1);
	}
	//printf("map[0]: %c", map[0][0]);
	/*map_x1 /= 40;
	map_x2 /= 40;
	map_y1 /= 40;
	map_y2 /= 40;*/

	printf("mapx1__2: %d\n", map_x1);
	printf("mapx2__2: %d\n", map_x2);
	printf("mapy1__2: %d\n", map_y1);
	printf("mapy2__2: %d\n", map_y2);
	
	printf("map[map_y1][map_x1]: %c\n", map[map_y1][map_x1]);
	printf("map[map_y1][map_x2]: %c\n", map[map_y1][map_x2]);
	printf("map[map_y2][map_x1]: %c\n", map[map_y2][map_x1]);
	printf("map[map_y2][map_x2]: %c\n", map[map_y2][map_x2]);
	
	if (map[map_y1][map_x1] == '1' || map[map_y1][map_x2] == '1' ||
		map[map_y2][map_x1] == '1' || map[map_y2][map_x2] == '1')
		return(0);
	return(1);
}

void	move_up(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x + vars->array->ray.dx * mouv_step;
	next_y = vars->player.pos.y + vars->array->ray.dy * mouv_step;
	printf("next_x: %f\n", vars->player.pos.x);
	printf("next_y: %f\n", vars->player.pos.x);
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x = next_x;
		vars->player.pos.y = next_y;
	}
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

void	move_down(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x - vars->array->ray.dx * mouv_step;
	next_y = vars->player.pos.y - vars->array->ray.dy * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x = next_x;
		vars->player.pos.y = next_y;
	}
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

void	move_right(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x + vars->array->ray.dx_side * mouv_step;
	next_y = vars->player.pos.y + vars->array->ray.dy_side * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x = next_x;
		vars->player.pos.y = next_y;
	}
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

void	move_left(struct s_vars *vars)
{
	float	next_x;
	float	next_y;

	next_x = vars->player.pos.x - vars->array->ray.dx_side * mouv_step;
	next_y = vars->player.pos.y - vars->array->ray.dy_side * mouv_step;
	if (check_margin(next_x, next_y, vars->array->map, 2))
	{
		vars->player.pos.x = next_x;
		vars->player.pos.y = next_y;
	}
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
}

void	clear_image(struct s_array *array, int width, int height)
{
	int	x, y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			ft_put_pixel(x, y, array, BLACK, 1);
			x++;
		}
		y++;
	}
}


void	render_frame(struct s_vars *vars)
{
	//clear_image(vars->array, vars->array->ray.width, vars->array->ray.height); // Efface tout avant de redessiner
	ft_init_line(&vars->array->ray, vars->array, &vars->player.pos);
	ft_draw_grid(vars->array);
	ft_draw_line(&vars->array->ray, vars->array, &vars->player.pos);
	fov(&vars->array->ray, vars->array, &vars->player.pos); //fonction necessaire au rendu 3d car elle cree l 'array de float
	ft_draw_half_screen(vars->array, vars->array->ray.width, vars->array->ray.height);
	draw_walls(&vars->array->ray, vars->array);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map, 0, 0);
}
