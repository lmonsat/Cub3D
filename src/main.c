/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:25 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 17:36:14 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	display_textures_grid(void *mlx, void *win, struct s_texture *textures)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	y = 0;
	while (i < NB_TEXTURES)
	{
		mlx_put_image_to_window(mlx, win, textures[i].img, x, y);
		x += textures[i].width + 5;
		if (x + textures[i].width > 800)
		{
			x = 0;
			y += textures[i].height + 5;
		}
		i++;
	}
}

void	free_close(struct s_vars *vars, struct s_array *array)
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
	free_path(vars->array);
}

// gerer les free en cas d erreur de chargement de textures
int	load_textures(struct s_vars *vars, struct s_texture *textures,
		struct s_array *array)
{
	char	*paths[4];
	int		i;

	i = 0;
	paths[0] = array->NO_path;
	paths[1] = array->EA_path;
	paths[2] = array->WE_path;
	paths[3] = array->SO_path;
	while (i < 4)
	{
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
	return (0);
}

void	check_arguments(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc == 1)
	{
		perror("Error\n Enter a map to read\n");
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		perror("Error\n Too many map to read, specify only 1 map\n");
		exit(EXIT_FAILURE);
	}
	else if (argc == 2)
	{
		while (argv[1][i] != '\0')
			i++;
		if (argv[1][i - 4] != '.' && argv[1][i - 3] != 'c' && argv[1][i
			- 2] != 'u' && argv[1][i - 1] != 'b')
		{
			perror("Error\n Not a .cub format\n");
			exit(EXIT_FAILURE);
		}
	}
}

int	main(int argc, char *argv[])
{
	struct s_vars		vars;
	struct s_array		array;
	struct s_game_stats	value;

	array.ray.hit_orien = 0;
	array.ray.tex_x = 0;
	array.ray.perp_tab = NULL;
	check_arguments(argc, argv);
	parse_map(&vars, &array, &value, argv);
	vars.stats = value;
	vars.array = &array;
	ft_memset(array.textures, 0, sizeof(array.textures));
	ft_game_loop(&vars, &array);
	free_1_array(&array);
	free_array(array.ceiling);
	free_array(array.floor);
	free_path(&array);
	return (0);
}
