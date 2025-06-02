/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/06/02 13:29:11 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_put_pixel(int x, int y, struct s_array *array, int color)
{
    char *pxl;

    if (x >= 0 && x < array->ray.width && y >= 0 && y < array->ray.height)
    {
        pxl = array->draw.addr + (y * array->line_len + x * (array->draw.bpp / 8));
        *(unsigned int *)pxl = color;
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
                ft_put_pixel(x, y, array, BLUE); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE);
        }
    }
    for (y = 0; y < array->ray.height; y += 40)
    {
        for (x = 0; x < array->ray.width; x++)
        {
            if (array->line[(int)y / 40][(int)x / 40] == '1')
                ft_put_pixel(x, y, array, BLUE); // Blanc
            else
                ft_put_pixel(x, y, array, WHITE);
        }
    }
}
