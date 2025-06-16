/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:33:25 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/17 01:21:41 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void	free_close(struct s_vars *vars, struct s_array *array)
{
	if (vars->mlx && vars->array->draw.img_game)
	{
		mlx_destroy_image(vars->mlx, vars->array->draw.img_game);
		vars->array->draw.img_game = NULL;
	}
	if (vars->mlx && vars->array->draw.img_map)
	{
		mlx_destroy_image(vars->mlx, vars->array->draw.img_map);
		vars->array->draw.img_map = NULL;
	}
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win_map);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	ft_cleanup_trace_line(&vars->array->ray);
	free_array(vars->array->map);
	free_array(vars->array->ceiling);
	free_array(vars->array->floor);
	//free_path(vars->array);
}

// gerer les free en cas d erreur de chargement de textures
static void	load_textures(struct s_vars *vars, struct s_texture *textures,
		struct s_array *array)
{
	char	*paths[4];
	int		i;

	i = 0;
	paths[0] = array->no_path;
	paths[1] = array->ea_path;
	paths[2] = array->we_path;
	paths[3] = array->so_path;
	while (i < 4)
	{
		/*printf("path %s", paths[i]);
		if (!paths[i])
		{
			exit(1);
		}*/
		textures[i].img = mlx_xpm_file_to_image(vars->mlx, paths[i],
				&textures[i].width, &textures[i].height);
		if (!textures[i].img)
		{
			printf("Error while loading textures\n");
			free_close(vars, array);
			exit(1);
		}
		textures[i].addr = mlx_get_data_addr(textures[i].img, &textures[i].bpp,
				&textures[i].line_len, &textures[i].endian);
		i++;
	}
}

void	init_array_colors(struct s_array *array)
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

void	init_graphics(struct s_vars *vars, struct s_array *array)
{
	array->ray.width = get_max_width(array->map) * 40;
	array->ray.height = get_max_height(array->map) * 40;
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
	{
		printf("MLX Error\n");
		exit(1);
	}
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
	load_textures(vars, array->textures, array);
}

void	ft_game_loop(struct s_vars *vars, struct s_array *array)
{
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
