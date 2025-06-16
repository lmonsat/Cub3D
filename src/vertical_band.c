/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_band.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:40:35 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 22:11:55 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int	shade_color(int color, int mod)
{
	int	a;
	int	r;
	int	g;
	int	b;

	a = color & 0xFF000000;
	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = (r * mod) / 255;
	g = (g * mod) / 255;
	b = (b * mod) / 255;
	return (a | (r << 16) | (g << 8) | b);
}

void	draw_wall_column(t_draw_vars *var, t_draw_band_info band,
		struct s_array *array)
{
	var->y = band.draw_start;
	while (var->y < band.draw_end)
	{
		if (var->y >= 0 && var->y < array->ray.height)
		{
			var->tex_y = (int)(((float)(var->y - band.draw_start)
						/ var->wall_height) * var->tex->height);
			if (var->tex_y >= var->tex->height)
				var->tex_y = var->tex->height - 1;
			var->tex_pixel = var->tex->addr + (var->tex_y * var->tex->line_len
					+ var->tex_x * (var->tex->bpp / 8));
			var->color = *(unsigned int *)var->tex_pixel;
			var->color = shade_color(var->color, var->mod);
			ft_put_pixel(var->x, var->y, array, var->color);
		}
		var->y++;
	}
}

void	draw_vertical_band(t_draw_band_info band, struct s_trace_line *pos,
		struct s_array *array)
{
	t_draw_vars	var;

	ft_init_var(&var, band, pos, array);
	if (var.wall_height <= 0)
		return ;
	while (var.x < band.x_start + band.band_width)
	{
		if (var.x >= 0 && var.x < array->ray.width)
			draw_wall_column(&var, band, array);
		var.x++;
	}
}

void	draw_walls(struct s_trace_line *pos, struct s_array *array)
{
	t_wall_render	r;

	ft_init_render(&r, array);
	while (r.i > 0)
	{
		if (r.i < r.remainder)
			r.band_width = r.base_band + 1;
		else
			r.band_width = r.base_band;
		r.dist = pos->perp_tab[r.i];
		if (r.dist <= 0.01f)
			r.dist = 0.01f;
		r.line_height = (int)(r.plane / r.dist);
		r.draw_start = (array->ray.height / 2) - (r.line_height / 2);
		r.draw_end = (array->ray.height / 2) + (r.line_height / 2);
		r.band.i = r.i;
		r.band.x_start = r.x_offset;
		r.band.band_width = r.band_width;
		r.band.draw_start = r.draw_start;
		r.band.draw_end = r.draw_end;
		draw_vertical_band(r.band, pos, array);
		r.x_offset += r.band_width;
		r.i--;
	}
}
