/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:33:25 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 17:39:18 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	init_array_colors(struct s_array *array)
{
	int	red;
	int	green;
	int	blue;

	red = ft_atoi(array->ceiling[0]);
	green = ft_atoi(array->ceiling[1]);
	blue = ft_atoi(array->ceiling[2]);
	array->ceiling_color = (red << 16) | (green << 8) | blue;
	red = ft_atoi(array->floor[0]);
	green = ft_atoi(array->floor[1]);
	blue = ft_atoi(array->floor[2]);
	array->floor_color = (red << 16) | (green << 8) | blue;
}

static int	init_graphics(struct s_vars *vars, struct s_array *array)
{
	array->ray.width = get_max_width(array->map) * 40;
	array->ray.height = get_max_height(array->map) * 40;
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
		return (1);
	vars->win = mlx_new_window(vars->mlx, array->ray.width, array->ray.height,
			"Cube3D");
	vars->win_map = mlx_new_window(vars->mlx, array->ray.width / 2,
			array->ray.height / 2, "Minimap");
	array->draw.img_game = mlx_new_image(vars->mlx, array->ray.width,
			array->ray.height);
	array->draw.img_map = mlx_new_image(vars->mlx, array->ray.width / 2,
			array->ray.height / 2);
	array->draw.addr = mlx_get_data_addr(array->draw.img_game, &array->draw.bpp,
			&array->line_len, &array->draw.endian);
	array->draw.addr_map = mlx_get_data_addr(array->draw.img_map,
			&array->draw.bpp_map, &array->line_len_map,
			&array->draw.endian_map);
	if (load_textures(vars, array->textures, array))
		return (1);
	return (0);
}

void	ft_game_loop(struct s_vars *vars, struct s_array *array)
{
	init_array_colors(array);
	if (init_graphics(vars, array))
		return ;
	vars->stats.mov_count = 0;
	array->ray.rotation = 0;
	mapping(array, vars);
	mlx_key_hook(vars->win, key_handler, vars);
	mlx_hook(vars->win, 17, 1L << 0, default_close, vars);
	mlx_loop(vars->mlx);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}
