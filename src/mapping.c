/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:52:46 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 22:44:01 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	mapping_case(struct s_array *array, struct s_vars *vars, int i, int j)
{
	if (array->map[i][j] == 'N' || array->map[i][j] == 'W'
		|| array->map[i][j] == 'E' || array->map[i][j] == 'S')
	{
		vars->player.pos.x_pixel = j * 40;
		vars->player.pos.y_pixel = i * 40;
		vars->player.pos.x = j;
		vars->player.pos.y = i;
		if (array->map[i][j] == 'N')
			array->ray.rotation = 270.0f;
		else if (array->map[i][j] == 'S')
			array->ray.rotation = 90.0f;
		else if (array->map[i][j] == 'E')
			array->ray.rotation = 0.0f;
		else if (array->map[i][j] == 'W')
			array->ray.rotation = 180.0f;
	}
}

void	mapping(struct s_array *array, struct s_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (array->map[i] != NULL)
	{
		j = 0;
		while (array->map[i][j] != '\0')
		{
			mapping_case(array, vars, i, j);
			j++;
		}
		i++;
	}
}

void	rotation_l(struct s_vars *vars)
{
	vars->array->ray.rotation -= 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0,
		0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map,
		0, 0);
}

void	rotation_r(struct s_vars *vars)
{
	vars->array->ray.rotation += 5;
	render_frame(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->array->draw.img_game, 0,
		0);
	mlx_put_image_to_window(vars->mlx, vars->win_map, vars->array->draw.img_map,
		0, 0);
}
