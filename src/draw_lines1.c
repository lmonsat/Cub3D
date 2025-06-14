/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/14 20:22:45 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	distance_central(struct s_array *array, struct s_position *player)
{
	float	ray_angle;
	float	raydirx;
	float	raydiry;

	ray_angle = array->ray.rotation * PI / 180.0f;
	raydirx = cos(ray_angle);
	raydiry = sin(ray_angle);
	ft_dda_draw_ray(player, raydirx, raydiry, array);
}

//dessine une ligne pixel par pixel
void	ft_draw_line(struct s_trace_line *pos, struct s_array *array,
		struct s_position *player)
{
	int	i;
	int	xi;
	int	yi;

	i = 0;
	pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
	pos->dx /= pos->step;
	pos->dy /= pos->step;
	while (i < 1000)
	{
		xi = (int)roundf(pos->x_start);
		yi = (int)roundf(pos->y_start);
		if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
			break ;
		if (array->map[yi / 40][xi / 40] == '1')
			break ;
		ft_put_pixel1(xi, yi, array, YELLOW);
		pos->x_start += pos->dx;
		pos->y_start += pos->dy;
		i++;
	}
	distance_central(array, player);
}

void	fov(struct s_trace_line *pos, struct s_array *array,
		struct s_position *player)
{
	int		i;
	float	x;
	float	y;

	ft_init_line(pos, array, player);
	x = pos->x_pass;
	y = pos->y_pass;
	i = -1;
	while (++i < NUM_RAYS / 2)
	{
		x -= pos->dx_step;
		y -= pos->dy_step;
	}
	i = -1;
	while (++i < NUM_RAYS)
	{
		x += pos->dx_step;
		y += pos->dy_step;
		ft_init_line1(pos, player, x, y);
		loop(pos, array, player);
		distance(array, player, i);
		pos->perp_tab[(NUM_RAYS - 1) - i] = pos->perpdist;
		pos->hit_orien[(NUM_RAYS - 1) - i] = pos->orientation;
	}
}
