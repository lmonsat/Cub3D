/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/04/04 19:28:45 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_put_pixel(int x, int y, struct s_array *array, int color)
{
	char *pxl;
	int width;
	int height;

	width = array->elmt.cols * 40;
	height = array->elmt.rows * 40;
	pxl = NULL;

	if (x >= 0 && x < width && y >= 0 && y < height)
	{
		pxl = array->draw.addr + (y * array->line_len + x
		* (array->draw.bpp / 8));
		*(unsigned int *)pxl = color;
	}
}

void ft_draw_grid(struct s_array *array, struct s_vars *vars)
{
    int x, y;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;

    // Dessiner les lignes verticales
    for (x = 0; x < width; x += 20)
    {
        for (y = 0; y < height; y++)
        {
            ft_put_pixel(x, y, array, WHITE); // Blanc
        }
    }

    // Dessiner les lignes horizontales
    for (y = 0; y < height; y += 20)
    {
        for (x = 0; x < width; x++)
        {
            ft_put_pixel(x, y, array, WHITE); // Blanc
        }
    }

    // Envoyer l'image mise à jour dans la fenêtre
    mlx_put_image_to_window(vars->mlx, vars->win, array->draw.img_ptr, 0, 0);
}

