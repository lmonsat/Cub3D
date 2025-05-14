/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/05/14 15:24:07 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/*void ft_put_pixel(int x, int y, struct s_array *array, int color)
{
	char *pxl;
	int w;
	int h;

	w = get_max_width(array->line);
	h = get_max_height(array->line);
    printf("w vaut %d et h vaut %d\n",w,h);
	pxl = NULL;

	if (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height)
	{
		pxl = array->draw.addr + (y * (array->ray.width * 8) + x
		* (array->draw.bpp / 8));
		*(unsigned int *)pxl = color;
	}
}*/
void ft_put_pixel(int x, int y, struct s_array *array, int color, int is_minimap)
{
    char *pxl;
	int map_x;
	int map_y;

    if (!is_minimap && (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height))
    {
        pxl = array->draw.addr + (y * array->line_len + x * (array->draw.bpp / 8));
        *(unsigned int *)pxl = color;
    }
    if (is_minimap)
    {
        map_x = x / 2;
        map_y = y / 2;
        if (map_x >= 0 && map_x < array->ray.width / 2 && map_y >= 0 && map_y < array->ray.height / 2)
        {
            pxl = array->draw.addr_map + (map_y * array->line_len_map + map_x * (array->draw.bpp_map / 8));
            *(unsigned int *)pxl = color;
        }
    }
}

void ft_draw_half_screen(struct s_array *array, int width, int height)
{
    int x, y;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            if (y < height / 2)
                ft_put_pixel(x, y, array, BLUE, 0);
            else
                ft_put_pixel(x, y, array, BROWN, 0);
        }
    }
}


void ft_draw_grid(struct s_array *array)
{
    int x, y;

    // Dessiner les lignes verticales
    for (x = 0; x < array->ray.width; x += 40)
    {
        for (y = 0; y < array->ray.height; y++)
        {
            if (array->line[(int)y / 40][(int)x / 40] == '1')
                ft_put_pixel(x, y, array, BLUE, 1); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE, 1);
        }
    }
    for (y = 0; y < array->ray.height; y += 40)
    {
        for (x = 0; x < array->ray.width; x++)
        {
            if (array->line[(int)y / 40][(int)x / 40] == '1')
                ft_put_pixel(x, y, array, BLUE, 1); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE, 1);
        }
    }
}
