/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/14 20:11:00 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

// Fonction pour l'affichage principal
void	ft_put_pixel(int x, int y, struct s_array *array, int color)
{
	char	*pxl;

	if (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height)
	{
		pxl = array->draw.addr + (y * array->line_len + x * (array->draw.bpp
					/ 8));
		*(unsigned int *)pxl = color;
	}
}

// Fonction pour l'affichage du minimap
void	ft_put_pixel1(int x, int y, struct s_array *array, int color)
{
	char	*pxl;
	int		map_x;
	int		map_y;

	map_x = x / 2;
	map_y = y / 2;
	if (map_x >= 0 && map_x < array->ray.width / 2 && map_y >= 0
		&& map_y < array->ray.height / 2)
	{
		pxl = array->draw.addr_map + (map_y * array->line_len_map + map_x
				* (array->draw.bpp_map / 8));
		*(unsigned int *)pxl = color;
	}
}

// dessine le floor et le ceiling en fonction de ce qui est demander
// dans map.cub
void	ft_draw_half_screen(struct s_array *array, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	while (y < height / 2)
	{
		x = 0;
		while (x < width)
		{
			ft_put_pixel(x, y, array, array->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < array->ray.height)
	{
		x = 0;
		while (x < array->ray.width)
		{
			ft_put_pixel(x, y, array, array->floor_color);
			x++;
		}
		y++;
	}
}

// a retirer
void	print_map(struct s_array *array)
{
	int	i;

	i = 0;
	if (!array || !array->map)
	{
		printf("array or array->map is NULL\n");
		return ;
	}
	while (array->map[i])
	{
		printf("map[%d]: %s\n", i, array->map[i]);
		i++;
	}
}

// Sécurité : éviter les invalid reads
static void	print_grid(struct s_array *array, int x, int y)
{
	int	map_y;
	int	map_x;

	map_y = y / 40;
	map_x = x / 40;
	if (!array->map || !array->map[map_y]
		|| map_x >= (int)ft_strlen(array->map[map_y]))
		return ;
	if (array->map[map_y][map_x] == '1')
		ft_put_pixel1(x, y, array, BLUE);
	if (array->map[map_y][map_x] == '0')
		ft_put_pixel1(x, y, array, YELLOW);
}

void	ft_draw_grid(struct s_array *array)
{
	int	x;
	int	y;

	x = 0;
	while (x < array->ray.width)
	{
		y = 0;
		while (y < array->ray.height)
		{
			print_grid(array, x, y);
			y++;
		}
		x += 40;
	}
	y = 0;
	while (y < array->ray.height)
	{
		x = 0;
		while (x < array->ray.width)
		{
			print_grid(array, x, y);
			x++;
		}
		y += 40;
	}
}
