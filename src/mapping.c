/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:52:46 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/04 02:08:37 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	rock(struct s_vars *vars, int x, int y)
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(vars->mlx, "./textures/rock.xpm", &img_width,
			&img_height);
	if (!img)
	{
		perror("Error\n Error while loading image.\n");
		mlx_destroy_image(vars->mlx, img);
		default_close(vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
	mlx_destroy_image(vars->mlx, img);
}

void	loading_player(struct s_vars *vars)
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(vars->mlx, "./textures/player.xpm", &img_width,
			&img_height);
	if (!img)
	{
		perror("Error\n Error while loading image.\n");
		mlx_destroy_image(vars->mlx, img);
		default_close(vars);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img, vars->player.pos.x_pixel,
		vars->player.pos.y_pixel);
	mlx_destroy_image(vars->mlx, img);
}

void	ground(struct s_vars *vars, int x, int y)
{
	void	*img;
	int		img_width;
	int		img_height;

	img = mlx_xpm_file_to_image(vars->mlx, "./textures/grass.xpm", &img_width,
			&img_height);
	if (!img)
	{
		perror("Error\n Error while loading image.\n");
		mlx_destroy_image(vars->mlx, img);
		default_close(vars);
		printf("fonction jamais atteinte");
		mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img, x, y);
	mlx_destroy_image(vars->mlx, img);
}

void    mapping_case(struct s_array *array, struct s_vars *vars, int i, int j)
{
    if (array->map[i][j] == 'N' || array->map[i][j] == 'W' || array->map[i][j] == 'E' || array->map[i][j] == 'S')
    {
        vars->player.pos.x_pixel = j * 40;
        vars->player.pos.y_pixel = i * 40;
		vars->player.pos.x = j;
        vars->player.pos.y = i;
		// Initialisation de la rotation en fonction de la direction
        if (array->map[i][j] == 'N')
            array->ray.rotation = 270.0f;  // Regarde vers le haut
        else if (array->map[i][j] == 'S')
            array->ray.rotation = 90.0f;   // Regarde vers le bas
        else if (array->map[i][j] == 'E')
            array->ray.rotation = 0.0f;    // Regarde vers la droite
        else if (array->map[i][j] == 'W')
            array->ray.rotation = 180.0f;  // Regarde vers la gauche
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

void	mapping_ground(struct s_array *array, struct s_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (array->line[i] != NULL)
	{
		j = 0;
		while (array->line[i][j] != '\0')
		{
			if (array->line[i][j] == '1' || array->line[i][j] == '0'
				|| array->line[i][j] == 'C' || array->line[i][j] == 'P'
				|| array->line[i][j] == 'E')
			{
				ground(vars, j * 40, i * 40);
			}
			j++;
		}
		i++;
	}
}
