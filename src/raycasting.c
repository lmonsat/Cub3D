/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/06/16 16:47:38 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_cleanup_trace_line(struct s_trace_line *pos)
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

void ft_init_line1(struct s_trace_line *pos, struct s_position *player, float x, float y)
{
    pos->ldx = x - player->x_pixel;
    pos->ldy = y - player->y_pixel;
    pos->step = fmaxf(fabsf(pos->ldx), fabsf(pos->ldy));
    pos->ldx /= pos->step;
    pos->ldy /= pos->step;
}

void ft_init_line2(struct s_trace_line *pos, struct s_position *player, float x, float y)
{
    pos->ldx = x - player->x_pixel;
    pos->ldy = y - player->y_pixel;
    pos->step = fmaxf(fabsf(pos->ldx), fabsf(pos->ldy));
    pos->ldx /= pos->step;
    pos->ldy /= pos->step;
}

void loop(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    float rx;
    float ry;
    int xi;
    int yi;
    int map_x;
    int map_y;

    rx = player->x_pixel;
    ry = player->y_pixel;
    while (1)
    {
        xi = (int)roundf(rx);
        yi = (int)roundf(ry);
        map_x = xi / 40;
        map_y = yi / 40;
        if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
        if (!array->map || !array->map[map_y] || map_x >= (int)ft_strlen(array->map[map_y]))
		        break;
        if (array->map[yi / 40][xi / 40] == '1')
                break;
        rx += pos->ldx;
        ry += pos->ldy;
    }
}

void ft_draw_circle(struct s_array *array, int centerX, int centerY, int radius, int color)
{
    int x, y;

    for (y = -radius; y <= radius; y++)
    {
        for (x = -radius; x <= radius; x++)
        {
            if (x * x + y * y <= radius * radius) // Vérifie si le point est dans le cercle
                ft_put_pixel1(centerX + x, centerY + y, array, color);
        }
    }
}

/*void draw_vertical_band(int i, int x_start, int band_width, int draw_start, int draw_end, struct s_trace_line *pos, struct s_array *array)
{
    int tex_x = pos->tex_x[i];
    int wall_height = draw_end - draw_start;
    if (wall_height <= 0) return;

    int orientation = pos->hit_orien[i];
    struct s_texture *tex = &array->textures[orientation];

    // Distance du rayon
    float dist = pos->perp_tab[i];
    if (dist < 0.1f) dist = 0.1f; // évite div/0

    // Calcul du facteur d'ombrage (simple, linéaire)
    float shade_factor = 1.0f / (1.0f + dist * 0.20f); // Ajuste 0.05f pour un rendu plus ou moins sombre
    int mod = (int)(shade_factor * 255.0f);
    if (mod > 255) mod = 255;
    if (mod < 50) mod = 50; // Ne pas totalement noircir

    for (int x = x_start; x < x_start + band_width; x++)
    {
        if (x < 0 || x >= array->ray.width)
            continue;

        for (int y = draw_start; y < draw_end; y++)
        {
            if (y < 0 || y >= array->ray.height)
                continue;

            int tex_y = (int)(((float)(y - draw_start) / wall_height) * tex->height);
            if (tex_y >= tex->height) tex_y = tex->height - 1;

            char *tex_pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
            int color = *(unsigned int *)tex_pixel;

            // Décompose le pixel
            int a = (color & 0xFF000000);
            int r = ((color & 0x00FF0000) >> 16);
            int g = ((color & 0x0000FF00) >> 8);
            int b = (color & 0x000000FF);

            // Applique l’ombrage
            r = (r * mod) / 255;
            g = (g * mod) / 255;
            b = (b * mod) / 255;

            color = a | (r << 16) | (g << 8) | b;

            ft_put_pixel(x, y, array, color);
        }
    }
}


void draw_walls(struct s_trace_line *pos, struct s_array *array)
{
    float fov_angle = 60.0f * (PI / 180.0f);
    int plane = (int)((array->ray.width / 2.0f) / tanf(fov_angle / 2.0f));

    int base_band = array->ray.width / NUM_RAYS;
    int remainder = array->ray.width % NUM_RAYS;
    int x_offset = 0;

    for (int i = NUM_RAYS - 1; i > 0; i--)
    {
        int band_width = base_band + (i < remainder ? 1 : 0); // répartit le reste
        float dist = pos->perp_tab[i];
        if (dist <= 0.01f)
            dist = 0.01f;

        int line_height = (int)(plane / dist);
        int draw_start = (array->ray.height / 2) - (line_height / 2);
        int draw_end = (array->ray.height / 2) + (line_height / 2);

        draw_vertical_band(i, x_offset, band_width, draw_start, draw_end, pos, array);
        x_offset += band_width;
    }
}*/
