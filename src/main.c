/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:25 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/11 16:32:37 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void display_textures_grid(void *mlx, void *win, struct s_texture *textures)
{
    int x = 0;
    int y = 0;

    for (int i = 0; i < NB_TEXTURES; i++)
    {
        mlx_put_image_to_window(mlx, win, textures[i].img, x, y);
        x += textures[i].width + 5; // espace entre les textures
        if (x + textures[i].width > 800) // passe à la ligne si trop large
        {
            x = 0;
            y += textures[i].height + 5;
        }
    }
}

/*int     load_textures(void *mlx, struct s_texture *textures)
{
    char *paths[NB_TEXTURES] = {T1, T2, T3, T4, T5, T6};
    int i;

    i = 0;
    while (i < NB_TEXTURES)
    {
        textures[i].img = mlx_xpm_file_to_image(mlx, paths[i], &textures[i].width, &textures[i].height);
        if(!textures[i].img)
        {
            printf("erreur de chargement de texture\n");
            return(1);
        }
        textures[i].addr = mlx_get_data_addr(textures[i].img, &textures[i].bpp, &textures[i].line_len, &textures[i].endian);
        i++;
    }
    return(0);
}*/

int     load_textures(void *mlx, struct s_texture *textures, struct s_array *array)
{
    printf("le path est %s", array->NO_path);
    printf("le path est %s", array->EA_path);
    printf("le path est %s", array->WE_path);
    printf("le path est %s", array->SO_path);

    char *paths[4] = {array->NO_path, array->EA_path, array->WE_path, array->SO_path};
    int i;

    i = 0;
    while (i < 4)
    {
        textures[i].img = mlx_xpm_file_to_image(mlx, paths[i], &textures[i].width, &textures[i].height);
        if(!textures[i].img)
        {
            printf("erreur de chargement de texture\n");
            return(1);
        }
        textures[i].addr = mlx_get_data_addr(textures[i].img, &textures[i].bpp, &textures[i].line_len, &textures[i].endian);
        i++;
    }
    return(0);
}

void	init_array_colors(struct s_array *array)
{
	array->ceiling_color = (ft_atoi(array->ceiling[0]) << 16) |
	                       (ft_atoi(array->ceiling[1]) << 8) |
	                       (ft_atoi(array->ceiling[2]));

	array->floor_color = (ft_atoi(array->floor[0]) << 16) |
	                     (ft_atoi(array->floor[1]) << 8) |
	                     (ft_atoi(array->floor[2]));
}

void	ft_game_loop(struct s_vars *vars, struct s_array *array)
{
    init_array_colors(array);
    array->ray.width = get_max_width(array->map) * 40;
    array->ray.height = get_max_height(array->map) * 40;
    vars->mlx = mlx_init();
    if (vars->mlx == NULL)
        return ;
    vars->win = mlx_new_window(vars->mlx, array->ray.width, array->ray.height, "Cube3D");
    vars->win_map = mlx_new_window(vars->mlx, array->ray.width / 2, array->ray.height / 2, "Minimap");
    array->draw.img_game = mlx_new_image(vars->mlx, array->ray.width, array->ray.height);
    array->draw.img_map = mlx_new_image(vars->mlx, array->ray.width / 2, array->ray.height / 2);
    array->draw.addr = mlx_get_data_addr(array->draw.img_game, &array->draw.bpp, &array->line_len, &array->draw.endian);
    array->draw.addr_map = mlx_get_data_addr(array->draw.img_map, &array->draw.bpp_map, &array->line_len_map, &array->draw.endian_map);
    if(load_textures(vars->mlx, array->textures, array))
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

    array.ray.hit_orien = 0;
    array.ray.tex_x = 0;
    array.ray.perp_tab = NULL;
	check_arguments(argc, argv);
    parse_map(&vars, &array, &value, argv);
    vars.stats = value;
    vars.array = &array;
    ft_game_loop(&vars, &array);
    free_1_array(&array);
	free_array(array.ceiling);
	free_array(array.floor);
	free_path(&array);
    return (0);
}
