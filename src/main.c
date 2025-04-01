/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:25 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/01 20:04:53 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	parse_map(struct s_vars *vars, struct s_array *array,
    struct s_game_stats *value, char *argv[])
{
    int	fd;

    fd = open_map_file(argv);
    check_first_line(fd, array);
    check_in_lines(fd, array);
    check_exit_player_collect(array, value);
    close(fd);
    check_characters_in_map(array);
    array->stats.nb_collectibles = value->nb_collectibles;
    array->backtracking = copy_array(array->line, array);
    backtracking(array, vars);
    vars->player.collected = 0;
    vars->array = array;
}

void	ft_game_loop(struct s_vars *vars, struct s_array *array)
{
    vars->mlx = mlx_init();
    if (vars->mlx == NULL)
    {
        return ;
    }
    vars->win = mlx_new_window(vars->mlx, array->elmt.cols * 40,
            array->elmt.rows * 40, "Steal and sleep");
    if (vars->win == NULL)
    {
        return ;
    }
    vars->stats.mov_count = 0;
    //mapping_ground(array, vars);
    //mapping(array, vars);
    mlx_key_hook(vars->win, key_handler, vars);
    mlx_hook(vars->win, 17, 1L << 0, default_close, vars);
    mlx_loop(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
    mlx_destroy_display(vars->mlx);
    free(vars->mlx);
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
        if (argv[1][i - 4] != '.' && argv[1][i - 3] != 'b' && argv[1][i
            - 2] != 'e' && argv[1][i - 1] != 'r')
        {
            perror("Error\n Not a .ber format\n");
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
    ft_game_loop(&vars, &array);
    free_tabs(&vars);
    free_visited(&array);
    return (0);
}