/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 23:22:07 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 23:16:38 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	init_line_dimensions(struct s_trace_line *pos, struct s_array *array,
		struct s_position *player)
{
	pos->width = get_max_width(array->map) * 40;
	pos->height = get_max_height(array->map) * 40;
	pos->x_start = player->x_pixel;
	pos->y_start = player->y_pixel;
	if (array->ray.rotation == 0)
		array->ray.rotation = 0.0f;
	array->ray.fov_angle = 2.0f * atanf((float)NUM_RAYS / CAM_DIST);
	array->ray.player_angle = array->ray.rotation * PI / 180.0f;
}

void	init_line_directions_and_camera(struct s_trace_line *pos,
		struct s_array *array, struct s_position *player)
{
	pos->dx = cosf(array->ray.rotation * PI / 180.0f);
	pos->dy = sinf(array->ray.rotation * PI / 180.0f);
	array->ray.dx = pos->dx;
	array->ray.dy = pos->dy;
	pos->dx_side = cosf((array->ray.rotation + 90.0f) * PI / 180.0f);
	pos->dy_side = sinf((array->ray.rotation + 90.0f) * PI / 180.0f);
	array->ray.dx_side = pos->dx_side;
	array->ray.dy_side = pos->dy_side;
	pos->x_pass = player->x_pixel + CAM_DIST * pos->dx;
	pos->y_pass = player->y_pixel + CAM_DIST * pos->dy;
}

void	init_line_step(struct s_trace_line *pos)
{
	pos->step = fmaxf(fabsf(pos->dx_side), fabsf(pos->dy_side));
	pos->dx_step = pos->dx_side / pos->step;
	pos->dy_step = pos->dy_side / pos->step;
}

void	init_line_allocation(struct s_trace_line *pos)
{
	ft_cleanup_trace_line(pos);
	pos->perp_tab = ft_calloc(sizeof(float), NUM_RAYS);
	if (!pos->perp_tab)
		exit(1);
	pos->hit_orien = ft_calloc(sizeof(int), NUM_RAYS);
	if (!pos->hit_orien)
		exit(1);
	pos->tex_x = ft_calloc(sizeof(int), NUM_RAYS);
	if (!pos->tex_x)
		exit(1);
}

void	ft_init_line(struct s_trace_line *pos, struct s_array *array,
		struct s_position *player)
{
	init_line_dimensions(pos, array, player);
	init_line_directions_and_camera(pos, array, player);
	init_line_step(pos);
	init_line_allocation(pos);
}
