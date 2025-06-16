/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:25 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 19:32:24 by drenquin         ###   ########.fr       */
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
	free_array(array.ceiling);
	free_array(array.floor);
	free_path(&array);
	return (0);
}
