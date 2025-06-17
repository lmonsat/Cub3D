/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:22 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/17 15:33:53 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	distance(struct s_array *array, struct s_position *player, int i)
{
	float	ray_angle;
	float	raydirx;
	float	raydiry;
	float	wall_x;
	int		tex_x;

	ray_angle = array->ray.player_angle - (array->ray.fov_angle / 2.0f) + (i
			* array->ray.fov_angle / NUM_RAYS);
	raydirx = cos(ray_angle);
	raydiry = sin(ray_angle);
	ft_dda_draw_ray(player, raydirx, raydiry, array);
	array->ray.perpdist = array->ray.brutdist * cos(ray_angle
			- array->ray.player_angle);
	if (array->ray.orientation == EAST || array->ray.orientation == WEST)
		wall_x = player->y_pixel / 40.0f + array->ray.perpdist * raydiry;
	else
		wall_x = player->x_pixel / 40.0f + array->ray.perpdist * raydirx;
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * TEX_WIDTH);
	if ((array->ray.orientation == EAST && raydirx < 0)
		|| (array->ray.orientation == NORTH && raydiry > 0))
		tex_x = TEX_WIDTH - tex_x - 1;
	array->ray.tex_x[(NUM_RAYS - 1) - i] = tex_x;
}

/* Permet de vérifier qu'il n'y a pas de caractère incohérent dans la map */
void	check_characters_in_map(struct s_array *array)
{
	int	i;
	int	j;

	i = 0;
	while (array->map[i] != NULL)
	{
		j = 0;
		while (array->map[i][j] != '\0')
		{
			if (!is_valid_char(array->map[i][j]))
			{
				perror("Error\n Map contains unneeded characters");
				if (array->map)
					free_array(array->map);
				free_array(array->line);
				free_array(array->sorted);
				free_array(array->ceiling);
				free_array(array->floor);
				free_path(array);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
