/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requested_player_move.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 00:53:27 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 16:25:34 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	delta_distances(float rayDirX, float rayDirY, float *deltaDistX,
		float *deltaDistY)
{
	if (rayDirX == 0)
		*deltaDistX = 1e30;
	else
		*deltaDistX = fabsf(1.0f / rayDirX);
	if (rayDirY == 0)
		*deltaDistY = 1e30;
	else
		*deltaDistY = fabsf(1.0f / rayDirY);
}

void	step_and_side_dist(t_dda *d, float rayDirX, float rayDirY)
{
	if (rayDirX < 0)
	{
		d->stepx = -1;
		d->sidedistx = (d->posx - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0f - d->posx) * d->deltadistx;
	}
	if (rayDirY < 0)
	{
		d->stepy = -1;
		d->sidedisty = (d->posy - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0f - d->posy) * d->deltadisty;
	}
}

void	perform_dda_loop(t_dda *d, struct s_array *array)
{
	while (!d->hit)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (d->mapx < 0 || d->mapy < 0 || d->mapx >= array->ray.width / 40
			|| d->mapy >= array->ray.width / 40)
			break ;
		if (array->map[d->mapy][d->mapx] == '1')
			d->hit = 1;
	}
}

void	set_ray_orientation(t_dda *d, float rayDirX, float rayDirY,
		struct s_array *array)
{
	if (d->side == 0)
	{
		array->ray.brutdist = d->sidedistx - d->deltadistx;
		if (rayDirX > 0)
			array->ray.orientation = EAST;
		else
			array->ray.orientation = WEST;
	}
	else
	{
		array->ray.brutdist = d->sidedisty - d->deltadisty;
		if (rayDirY > 0)
			array->ray.orientation = SOUTH;
		else
			array->ray.orientation = NORTH;
	}
}

void	ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY,
		struct s_array *array)
{
	t_dda	d;

	d.posx = player->x_pixel / 40.0f;
	d.posy = player->y_pixel / 40.0f;
	d.mapx = (int)d.posx;
	d.mapy = (int)d.posy;
	d.hit = 0;
	d.side = 0;
	delta_distances(rayDirX, rayDirY, &d.deltadistx, &d.deltadisty);
	step_and_side_dist(&d, rayDirX, rayDirY);
	perform_dda_loop(&d, array);
	set_ray_orientation(&d, rayDirX, rayDirY, array);
}
