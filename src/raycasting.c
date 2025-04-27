/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmonsat <lmonsat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 17:56:33 by lmonsat           #+#    #+#             */
/*   Updated: 2025/04/01 19:21:51 by lmonsat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void ft_init_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    pos->width = array->elmt.cols * 40;
    pos->height = array->elmt.rows * 40;
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->dx = cosf(array->ray.rotation * PI / 180.0f);
    pos->dy = sinf(array->ray.rotation * PI / 180.0f);
    pos->x_pass = player->x_pixel;
    pos->y_pass = player->y_pixel;
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

/*void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array)
{
    // Conversion des coordonnées du joueur en position de case (cellule) sur la grille
    int mapX = (int)(player->x_pixel / 40);
    int mapY = (int)(player->y_pixel / 40);

    // Calcul des distances qu'un rayon doit parcourir pour traverser une cellule en X ou en Y
    float deltaDistX = fabsf(1.0f / rayDirX);
    float deltaDistY = fabsf(1.0f / rayDirY);

    // Déclaration des variables de direction
    int stepX, stepY;
    float sideDistX, sideDistY;
    float distance = 0.0f; // Variable qui stockera la distance finale du rayon au mur

    // Détermination des directions de déplacement en X
    if (rayDirX < 0)
    {
        printf("gauche");
        stepX = -1; // Déplacement vers la gauche
        sideDistX = (player->x_pixel - mapX * 40) / 40 * deltaDistX; // Distance à la prochaine frontière de cellule
    }
    else
    {
        printf("droite");
        stepX = 1; // Déplacement vers la droite
        sideDistX = ((mapX + 1) * 40 - player->x_pixel) / 40 * deltaDistX; // Distance à la prochaine frontière de cellule
    }

    // Détermination des directions de déplacement en Y
    if (rayDirY < 0)
    {
        printf("haut");
        stepY = -1; // Déplacement vers le haut
        sideDistY = (player->y_pixel - mapY * 40) / 40 * deltaDistY; // Distance à la prochaine frontière de cellule
    }
    else
    {
        printf("bas");
        stepY = 1; // Déplacement vers le bas
        sideDistY = ((mapY + 1) * 40 - player->y_pixel) / 40 * deltaDistY; // Distance à la prochaine frontière de cellule
    }

    int hit = 0; // Variable pour détecter la collision avec un mur
    //int side; // Indique si la collision s'est produite sur un côté horizontal ou vertical

    // Initialisation des coordonnées du rayon
    float rayX = player->x_pixel;
    float rayY = player->y_pixel;

    // Boucle DDA : progression du rayon cellule par cellule jusqu'à toucher un mur
    while (!hit)
    {
        // Colorie la case traversée pour visualiser le trajet du rayon
        //ft_put_pixel((int)rayX, (int)rayY, array, GREEN);
        ft_draw_circle(array,(int)rayX, (int)rayY, 2, YELLOW);

        // Détermination de la direction la plus courte pour avancer le rayon
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX; // Ajoute la distance pour traverser une cellule en X
            mapX += stepX; // Avance d'une cellule dans la direction X
            //side = 0; // Indique que la collision est en X
            distance += deltaDistX; // Ajoute la distance parcourue
        }
        else
        {
            sideDistY += deltaDistY; // Ajoute la distance pour traverser une cellule en Y
            mapY += stepY; // Avance d'une cellule dans la direction Y
            //side = 1; // Indique que la collision est en Y
            distance += deltaDistY; // Ajoute la distance parcourue
        }

        // Mise à jour des coordonnées du rayon (centre de la cellule actuelle)
        rayX = mapX * 40 + 0;
        rayY = mapY * 40 + 0;

        // Vérification des limites de la carte
        if (mapX < 0 || mapY < 0 || mapX >= array->elmt.cols || mapY >= array->elmt.rows)
            break;

        // Si on touche un mur (cellule contenant '1'), arrêt de la boucle
        if (array->line[mapY][mapX] == '1')
        {
            ft_put_pixel(rayX, rayY, array, RED); // Colorie la case touchée en rouge pour indiquer un mur
            ft_draw_circle(array,(int)rayX, (int)rayY, 2, YELLOW);
            hit = 1;
        }
    }

    // Affichage de la distance du rayon au mur détecté
    printf("Distance au mur : %f\n", distance);
}*/

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
    //printf("delta dist x vaux %f\n", deltaDistX);
    //printf("delta dist y vaux %f\n", deltaDistY);

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
    int side = 0; // 0 = X side, 1 = Y side

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
        if (mapX < 0 || mapY < 0 || mapX >= array->elmt.cols || mapY >= array->elmt.rows)
            break;

        if (array->line[mapY][mapX] == '1')
        {
            // Dessine un cercle à l’impact
            ft_draw_circle(array, mapX * 40, mapY * 40, 5, YELLOW);
            hit = 1;
        }
    }

    // Calcul correct de la distance projetée
    float distance;
    if (side == 0)
        distance = (mapX - posX + (1.0f - stepX) / 2.0f) / rayDirX;
    else
        distance = (mapY - posY + (1.0f - stepY) / 2.0f) / rayDirY;

    //float distance_pixels = distance * 40.0f;

    //float dot = rayDirX * player->dir_x + rayDirY * player->dir_y;
    //float corrected_distance = distance * dot;
    
    // Affichage de la distance
    printf("Distance au mur (cases) : %f\n", distance);
    //printf("Distance au mur (pixels) : %f\n", distance_pixels);
}

/*void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array, float angle_ray, float angle_player)
{
    float posX = player->x_pixel / 40.0f;
    float posY = player->y_pixel / 40.0f;

    int mapX = (int)posX;
    int mapY = (int)posY;

    float deltaDistX = (rayDirX == 0) ? 1e30 : fabsf(1.0f / rayDirX);
    float deltaDistY = (rayDirY == 0) ? 1e30 : fabsf(1.0f / rayDirY);

    int stepX, stepY;
    float sideDistX, sideDistY;

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

        if (mapX < 0 || mapY < 0 || mapX >= array->elmt.cols || mapY >= array->elmt.rows)
            break;

        if (array->line[mapY][mapX] == '1')
        {
            ft_put_pixel(mapX * 40, mapY * 40, array, RED);
            ft_draw_circle(array, mapX * 40, mapY * 40, 2, YELLOW);
            hit = 1;
        }
    }

    // Distance brute
    float distance;
    if (side == 0)
        distance = (mapX - posX + (1.0f - stepX) / 2.0f) / rayDirX;
    else
        distance = (mapY - posY + (1.0f - stepY) / 2.0f) / rayDirY;

    // 🔧 Correction fish-eye
    float angle_diff = angle_ray - angle_player;
    float distance_corrected = distance * cosf(angle_diff); // projection perpendiculaire

    float distance_pixels = distance_corrected * 40.0f;

    printf("Distance corrigée au mur (cases) : %f\n", distance_corrected);
    printf("Distance corrigée au mur (pixels) : %f\n", distance_pixels);
}*/


