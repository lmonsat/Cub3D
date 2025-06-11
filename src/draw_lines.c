/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/11 13:56:12 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

// Fonction pour l'affichage principal
void ft_put_pixel(int x, int y, struct s_array *array, int color)
{
    char *pxl;

    if (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height)
    {
        pxl = array->draw.addr + (y * array->line_len + x * (array->draw.bpp / 8));
        *(unsigned int *)pxl = color;
    }
}

// Fonction pour l'affichage du minimap
void ft_put_pixel1(int x, int y, struct s_array *array, int color)
{
    char *pxl;
    int map_x = x / 2;
    int map_y = y / 2;

    if (map_x >= 0 && map_x < array->ray.width / 2 && map_y >= 0 && map_y < array->ray.height / 2)
    {
        pxl = array->draw.addr_map + (map_y * array->line_len_map + map_x * (array->draw.bpp_map / 8));
        *(unsigned int *)pxl = color;
    }
}

//dessine le floor et le ceiling en fonction de ce qui est demander
//dans map.cub
void ft_draw_half_screen(struct s_array *array, int width, int height)
{
	int		x;
	int		y;

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


static void print_grid(struct s_array *array, int x, int y)
{
	if (array->map[(int)y / 40][(int)x / 40] == '1')
		ft_put_pixel1(x, y, array, BLUE);
	else
		ft_put_pixel1(x, y, array, WHITE);
}

void ft_draw_grid(struct s_array *array)
{
    int x;
    int y;

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
