/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   margin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:11:21 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/16 19:14:03 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	ft_init_margin(t_margin_data *d, char **map)
{
	d->max_y = 0;
	d->max_x = 0;
	while (map[d->max_y])
		d->max_y++;
	while (map[0][d->max_x])
		d->max_x++;
}

void	ft_init_margin1(t_margin_data *d, float x, float y, int margin)
{
	d->map_x1 = (int)(x + margin) / 40;
	d->map_x2 = (int)(x - margin) / 40;
	d->map_y1 = (int)(y + margin) / 40;
	d->map_y2 = (int)(y - margin) / 40;
}

int	check_margin(float x, float y, char **map, int margin)
{
	t_margin_data	d;

	if (!map || !map[0])
	{
		printf("Erreur : map ou map[0] non initialisé\n");
		exit(1);
	}
	ft_init_margin(&d, map);
	ft_init_margin1(&d, x, y, margin);
	if (d.map_x1 < 0 || d.map_x1 >= d.max_x || d.map_x2 < 0
		|| d.map_x2 >= d.max_x || d.map_y1 < 0 || d.map_y1 >= d.max_y
		|| d.map_y2 < 0 || d.map_y2 >= d.max_y)
		return (0);
	if (!map[d.map_y1] || !map[d.map_y2])
		return (0);
	if (map[d.map_y1][d.map_x1] == '1' || map[d.map_y1][d.map_x2] == '1'
		|| map[d.map_y2][d.map_x1] == '1' || map[d.map_y2][d.map_x2] == '1')
		return (0);
	return (1);
}
