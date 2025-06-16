/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   band_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:05:22 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 22:07:41 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_init_var(t_draw_vars *var, t_draw_band_info band,
		struct s_trace_line *pos, struct s_array *array)
{
	var->tex_x = pos->tex_x[band.i];
	var->wall_height = band.draw_end - band.draw_start;
	var->orientation = pos->hit_orien[band.i];
	var->tex = &array->textures[var->orientation];
	var->dist = pos->perp_tab[band.i];
	if (var->dist < 0.1f)
		var->dist = 0.1f;
	var->shade_factor = 1.0f / (1.0f + var->dist * 0.20f);
	var->mod = (int)(var->shade_factor * 255.0f);
	if (var->mod > 255)
		var->mod = 255;
	if (var->mod < 50)
		var->mod = 50;
	var->x = band.x_start;
}

void	ft_init_render(t_wall_render *r, struct s_array *array)
{
	r->fov_angle = 60.0f * (PI / 180.0f);
	r->plane = (int)((array->ray.width / 2.0f) / tanf(r->fov_angle / 2.0f));
	r->base_band = array->ray.width / NUM_RAYS;
	r->remainder = array->ray.width % NUM_RAYS;
	r->x_offset = 0;
	r->i = NUM_RAYS - 1;
}
