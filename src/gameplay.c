/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:22 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/14 20:26:25 by drenquin         ###   ########.fr       */
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
	tex_x = (int)(wall_x * tex_width);
	if ((array->ray.orientation == EAST && raydirx < 0)
		|| (array->ray.orientation == NORTH && raydiry > 0))
		tex_x = tex_width - tex_x - 1;
	array->ray.tex_x[(NUM_RAYS - 1) - i] = tex_x;
}
