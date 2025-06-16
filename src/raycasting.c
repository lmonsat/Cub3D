/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 22:02:42 by drenquin         ###   ########.fr       */
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
	t_loop	l;

	l.rx = player->x_pixel;
	l.ry = player->y_pixel;
	while (1)
	{
		l.xi = (int)roundf(l.rx);
		l.yi = (int)roundf(l.ry);
		l.map_x = l.xi / 40;
		l.map_y = l.yi / 40;
		if (l.xi < 0 || l.xi >= pos->width || l.yi < 0 || l.yi >= pos->height)
			break ;
		if (!array->map || !array->map[l.map_y]
			|| l.map_x >= (int)ft_strlen(array->map[l.map_y]))
			break ;
		if (array->map[l.yi / 40][l.xi / 40] == '1')
			break ;
		l.rx += pos->ldx;
		l.ry += pos->ldy;
	}
}
