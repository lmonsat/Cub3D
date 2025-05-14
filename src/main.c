/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:25 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/14 16:40:08 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

static void mlx_ptr_init(struct s_vars *vars, struct s_array *array)
{
    array->ray.width = get_max_width(array->line) * 40;
    array->ray.height = get_max_height(array->line) * 40;
    vars->mlx = mlx_init();
    if (vars->mlx == NULL)
        return ;
    vars->win = mlx_new_window(vars->mlx, array->ray.width, array->ray.height, "Cube3D");
    vars->win_map = mlx_new_window(vars->mlx, array->ray.width / 2, array->ray.height / 2, "Minimap");
    array->draw.img_game = mlx_new_image(vars->mlx, array->ray.width, array->ray.height);
    array->draw.img_map = mlx_new_image(vars->mlx, array->ray.width / 2, array->ray.height / 2);
    array->draw.addr = mlx_get_data_addr(array->draw.img_game, &array->draw.bpp, &array->line_len, &array->draw.endian);
    array->draw.addr_map = mlx_get_data_addr(array->draw.img_map, &array->draw.bpp_map, &array->line_len_map, &array->draw.endian_map);
    vars->stats.mov_count = 0;
    array->ray.rotation = 0;
}

static void	ft_game_loop(struct s_vars *vars, struct s_array *array)
{

    mlx_key_hook(vars->win, key_handler, vars);
    mlx_hook(vars->win, 17, 1L << 0, default_close, vars);
    mlx_loop(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_display(vars->mlx);
    free(vars->mlx);
}

static void	check_arguments(int argc, char *argv[])
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
        if (argv[1][i - 4] != '.' && argv[1][i - 3] != 'c' && argv[1][i - 2] != 'u' && argv[1][i - 1] != 'b')
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

	check_arguments(argc, argv);
    parse_map(&vars, &array, &value, argv);
    vars.stats = value;
    vars.array = &array;
	mlx_ptr_init(&vars, &array);
	render_frame(&vars);
    ft_game_loop(&vars, &array);
    free_1_array(&array);
	free_array(array.ceiling);
	free_array(array.floor);
	free_path(&array);
    return (0);
}
