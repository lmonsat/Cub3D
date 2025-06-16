/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 18:52:56 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_cleanup_trace_line(struct s_trace_line *pos)
{
	if (pos->perp_tab)
	{
		free(pos->perp_tab);
		pos->perp_tab = NULL;
	}
	if (pos->hit_orien)
	{
		free(pos->hit_orien);
		pos->hit_orien = NULL;
	}
	if (pos->tex_x)
	{
		free(pos->tex_x);
		pos->tex_x = NULL;
	}
}

void	ft_init_line1(struct s_trace_line *pos, struct s_position *player,
		float x, float y)
{
	pos->ldx = x - player->x_pixel;
	pos->ldy = y - player->y_pixel;
	pos->step = fmaxf(fabsf(pos->ldx), fabsf(pos->ldy));
	pos->ldx /= pos->step;
	pos->ldy /= pos->step;
}

void	ft_init_line2(struct s_trace_line *pos, struct s_position *player,
		float x, float y)
{
	pos->ldx = x - player->x_pixel;
	pos->ldy = y - player->y_pixel;
	pos->step = fmaxf(fabsf(pos->ldx), fabsf(pos->ldy));
	pos->ldx /= pos->step;
	pos->ldy /= pos->step;
}

void	loop(struct s_trace_line *pos, struct s_array *array,
		struct s_position *player)
{
	float	rx;
	float	ry;
	int		xi;
	int		yi;
	int		map_x;
	int		map_y;

	rx = player->x_pixel;
	ry = player->y_pixel;
	while (1)
	{
		xi = (int)roundf(rx);
		yi = (int)roundf(ry);
		map_x = xi / 40;
		map_y = yi / 40;
		if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
			break ;
		if (!array->map || !array->map[map_y]
			|| map_x >= (int)ft_strlen(array->map[map_y]))
			break ;
		if (array->map[yi / 40][xi / 40] == '1')
			break ;
		rx += pos->ldx;
		ry += pos->ldy;
	}
}

void	ft_draw_circle(struct s_array *array, int centerX, int centerY,
		int radius, int color)
{
	int x, y;
	for (y = -radius; y <= radius; y++)
	{
		for (x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
				ft_put_pixel1(centerX + x, centerY + y, array, color);
		}
	}
}
