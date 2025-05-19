/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/05/19 20:52:33 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_init_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    pos->width = get_max_width(array->line) * 40;
    pos->height = get_max_height(array->line) * 40;
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;

    //permet des mouvements avant arriere sur l' axe du joueur
    pos->dx = cosf(array->ray.rotation * PI / 180.0f);
    pos->dy = sinf(array->ray.rotation * PI / 180.0f);

    //permet des mouvement gauche droite sur l' axe du joueur
    pos->dx_side = cosf((array->ray.rotation + 90.0f) * PI / 180.0f);
    pos->dy_side = sinf((array->ray.rotation + 90.0f) * PI / 180.0f);

    //defini la distance entre le joueur et le plan caméra
    pos->x_pass = player->x_pixel + cam_dist * pos->dx;
    pos->y_pass = player->y_pixel + cam_dist * pos->dy;

    pos->step = fmaxf(fabsf(pos->dx_side), fabsf(pos->dy_side));
    pos->dx_step = pos->dx_side / pos->step;
    pos->dy_step = pos->dy_side / pos->step;
	if (pos->perp_tab)
    	free(pos->perp_tab);	// free pour chaque frame de généré l'ancien perp_tab
	pos->perp_tab = calloc(sizeof(float), NUM_RAYS);	// utilisation de calloc, pour l'initialisation a zéro
	if (pos->perp_tab == NULL)
		exit(1);
    if (pos->hit_orien)
        free(pos->hit_orien);
    pos->hit_orien = calloc(sizeof(int), NUM_RAYS);
    if (pos->hit_orien == NULL)
        exit(1);
    if (pos->tex_x)
        free(pos->tex_x);
    pos->tex_x = calloc(sizeof(int), NUM_RAYS);
    if (pos->tex_x == NULL)
        exit(1);
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
    int i;

    i = 0;
    rx = player->x_pixel;
    ry = player->y_pixel;
    while (i < 1000)
    {
        xi = (int)roundf(rx);
        yi = (int)roundf(ry);
        if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
        if (array->line[yi / 40][xi / 40] == '1')
                break;
        ft_put_pixel(xi, yi, array, RED);
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
                ft_put_pixel(centerX + x, centerY + y, array, color);
        }
    }
}

void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array)
{
    // Position du joueur convertie en cases
    float posX = player->x_pixel / 40.0f;
    float posY = player->y_pixel / 40.0f;

    int mapX = (int)posX;
    int mapY = (int)posY;

    // Calculs des delta distances
    float deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1.0f / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1.0f / rayDirY);

    int stepX, stepY;
    float sideDistX, sideDistY;

    // Calcul step et sideDist en X
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0f - posX) * deltaDistX;
    }

    // Calcul step et sideDist en Y
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0f - posY) * deltaDistY;
    }

    int hit = 0;
    int side = 0;
    // 0 = X side, 1 = Y side

    // Boucle DDA
    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        // Vérifie les limites
        if (mapX < 0 || mapY < 0 || mapX >= get_max_width(array->line) || mapY >= get_max_height(array->line))
            break;
        if (array->line[mapY][mapX] == '1')
        {
            hit = 1;
        }
    }
    //float perpWallDist;
    if(side == 0) // Ray a frappé un mur vertical (Est/Ouest)
    {
        array->ray.brutdist = (sideDistX - deltaDistX);
        if (rayDirX > 0)
            array->ray.orientation = EAST;
        else
            array->ray.orientation = WEST;
    }
    else // Ray a frappé un mur horizontal (Nord/Sud)
    {
        array->ray.brutdist = (sideDistY - deltaDistY);
        if (rayDirY > 0)
            array->ray.orientation = SOUTH;
        else
            array->ray.orientation = NORTH;
    }
}

/*void draw_vertical_band(int x_start, int band_width, int draw_start, int draw_end, struct s_array *array)
{
    for (int x = x_start; x < x_start + band_width; x++)
    {
        if (x < 0 || x >= array->ray.width)
            continue;
        for (int y = draw_start; y <= draw_end; y++)
        {
            if (y >= 0 && y < array->ray.height)
                ft_put_pixel(x, y, array, GRAY); // couleur du mur
        }
    }
}*/

void draw_vertical_band(int i, int x_start, int band_width, int draw_start, int draw_end, struct s_trace_line *pos, struct s_array *array)
{
    int tex_x = pos->tex_x[i];             // coordonnée x dans la texture
    int wall_height = draw_end - draw_start;
    if (wall_height <= 0) return;

    int orientation = pos->hit_orien[i];   // 0=N, 1=S, 2=E, 3=W
    struct s_texture *tex = &array->textures[orientation];

    for (int x = x_start; x < x_start + band_width; x++)
    {
        if (x < 0 || x >= array->ray.width)
            continue;

        for (int y = draw_start; y < draw_end; y++)
        {
            if (y < 0 || y >= array->ray.height)
                continue;

            // coordonnée y dans la texture
            int tex_y = (int)(((float)(y - draw_start) / wall_height) * tex->height);
            if (tex_y >= tex->height) tex_y = tex->height - 1;

            // Calcul adresse pixel texture
            char *tex_pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
            int color = *(unsigned int *)tex_pixel;

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

    for (int i = 0; i < NUM_RAYS; i++)
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
}
