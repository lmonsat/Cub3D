/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drenquin <drenquin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:28:45 by drenquin          #+#    #+#             */
/*   Updated: 2025/04/14 17:18:31 by drenquin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

/*void ft_init_line(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    pos->width = array->elmt.cols * 40;
    pos->height = array->elmt.rows * 40;
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    //pos->x_pass = ...
    //pos->y_pass = ...

    //vecteurs de direction partant vers la droite 
    pos->dx = pos->x_pass - player->x_pixel;
    pos->dy = pos->y_pass - player->y_pixel;

}*/
//attention cette fonction modifie mon point de depart pos->x.. me referer a player_x...
//que je ne modifie pas afin de garder la position du joueur en memoire 
//pos-> x et y_pass a redefinir a chaque utilisation de la fonction
void ft_draw_line(struct s_trace_line *pos, struct s_array *array)
{

   //int width;
   //int height;
   int i;
   int xi;
   int yi;

   i = 0;
   //width = array->elmt.cols * 40;
   //height = array->elmt.rows * 40;

   //position de départ
   //pos->x_start = player->x_pixel;
   //pos->y_start = player->y_pixel;

   //point de passage de la line (ligne qui va problement devenir facultative)
   //pos->x_pass = width / 2;
   //pos->y_pass = height / 2;

   //vecteur de direction
   //pos->dx = pos->x_pass - player->x_pixel;
   //pos->dy = pos->y_pass - player->y_pixel;
   //pos->dx = cosf(0.0f * PI / 180.0f);
   //pos->dy = sinf(0.0f * PI / 180.0f);

   printf("pos dx est egale a %f\n", pos->dx);
   printf("pos dy est egale a %f\n", pos->dy);

   pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
   pos->dx /= pos->step;
   pos->dy /= pos->step;

   while (i < 1000)
   {
        xi = (int)roundf(pos->x_start);
        yi = (int)roundf(pos->y_start);
        if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
            break;
        if (array->line[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel(xi, yi, array, RED);
        pos->x_start += pos->dx;
        pos->y_start += pos->dy;
        i++;
   }
}

void ft_perpendiculare(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i = 0;
    int xi, yi;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;
    float x;
    float y;
    
    // Repartir du joueur
    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->x_pass = player->x_pixel;
    pos->y_pass = player->y_pixel;
    
    //decale la perpendiculaire par rapport au joueur
    while (i < 80)
    {
        pos->x_start += pos->dx;
        pos->y_start += pos->dy;
        i++;
    }
    
    // Calcul du vecteur perpendiculaire
    float tmp_dx = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp_dx;

    
    printf("pos dx perpendiculaire egale a %f\n", pos->dx);
    printf("pos dy perpendiculaire egale a %f\n", pos->dy);

    x = pos->x_start;
    y = pos->y_start;

    i = 0;
    while (i < 25)
    {
        xi = (int)roundf(pos->x_start);
        yi = (int)roundf(pos->y_start);
        if (xi < 0 || xi >= width || yi < 0 || yi >= height)
            break;
        if (array->line[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel(xi, yi, array, YELLOW);
        pos->x_start += pos->dx;
        pos->y_start += pos->dy;
        i++;
    }

    i = 0;
    while (i < 25)
    {
        xi = (int)roundf(x);
        yi = (int)roundf(y);
        if (xi < 0 || xi >= width || yi < 0 || yi >= height)
            break;
        if (array->line[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel(xi, yi, array, BLUE);
        x -= pos->dx;
        y -= pos->dy;
        i++;
    }
}
/*void ft_fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{

    int i;
    int xi, yi;
    int width = array->elmt.cols * 40;
    int height = array->elmt.rows * 40;
    //float tmp_dx;

    pos->x_start = player->x_pixel;
    pos->y_start = player->y_pixel;
    pos->x_pass = player->x_pixel;
    pos->y_pass = player->y_pixel;
    
    pos->dx = pos->x_pass - player->x_pixel;
    pos->dy = pos->y_pass - player->y_pixel;

    i = 0;
    while (i < 80)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        i++;
    }
    


    float tmp_dx = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp_dx;

    while (i < 50)
    {
        xi = (int)roundf(pos->x_pass);
        yi = (int)roundf(pos->y_pass);
        if (xi < 0 || xi >= width || yi < 0 || yi >= height)
            break;
        if (array->line[yi / 40][xi / 40] == '1')
            break;
        ft_put_pixel(xi, yi, array, GREEN);
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        i++;
    }

}*/

/*void ft_fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    float base_dx = pos->dx;
    float base_dy = pos->dy;

    float angle_fov = 60.0f * (PI / 180.0f); // FOV en radians (ici 60°)
    float angle_step = angle_fov / 60.0f;      // 60 rayons => 1 par degré environ

    float mid_angle = atan2f(base_dy, base_dx); // angle de la direction actuelle
    float angle;
    int i = 0;

    while (i < 60)
    {
        angle = mid_angle - (angle_fov / 2.0f) + i * angle_step;

        // Crée un nouveau vecteur direction à partir de l'angle
        pos->dx = cosf(angle);
        pos->dy = sinf(angle);

        ft_draw_line(pos, array, player);

        i++;
    }

    // Réinitialiser la direction d’origine si besoin
    pos->dx = base_dx;
    pos->dy = base_dy;
}*/

/*void fov_half(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i;
    int j;
    int xi;
    int yi;
    float tmp;
    float x;
    float y;
    float ldx;
    float ldy;

    i = 0;
    j = 0;
    ft_init_line(pos, array, player);
    while (i < 80)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        i++;  
    }
    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;
    
    pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
    pos->dx /= pos->step;
    pos->dy /= pos->step;

    i = 0;
    while(i < 50)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        ldx = pos->x_pass - player->x_pixel;
        ldy = pos->y_pass - player->y_pixel;
        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;
        x = player->x_pixel;
        y = player->y_pixel;
        j = 0;
        while (j < 1000)
        {
            xi = (int)roundf(x);
            yi = (int)roundf(y);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            x += ldx;
            y += ldy;
            j++; 
        }
        i++;
    }
}*/

/*void fov_other(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i;
    int j;
    int xi;
    int yi;
    float tmp;
    float x;
    float y;
    float ldx;
    float ldy;

    i = 0;
    j = 0;
    ft_init_line(pos, array, player);
    while (i < 80)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        i++;  
    }
    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;
    
    pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
    pos->dx /= pos->step;
    pos->dy /= pos->step;

    i = 0;
    while(i < 50)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
        ldx = pos->x_pass - player->x_pixel;
        ldy = pos->y_pass - player->y_pixel;
        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;
        x = player->x_pixel;
        y = player->y_pixel;
        j = 0;
        while (j < 1000)
        {
            xi = (int)roundf(x);
            yi = (int)roundf(y);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            x -= ldx;
            y -= ldy;
            j++; 
        }
        i++;
    }
}*/

/*void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i, j;
    int xi, yi;
    float ldx, ldy;
    float angle_fov = 60.0f * (PI / 180.0f); // FOV en radians
    float angle_step = angle_fov / 60.0f;
    float mid_angle = atan2f(pos->dy, pos->dx); // direction actuelle
    float angle;
    float tmp;

    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;

    for (i = 0; i < 60; i++)
    {
        angle = mid_angle - (angle_fov / 2.0f) + i * angle_step;

        ldx = cosf(angle);
        ldy = sinf(angle);

        float x = player->x_pixel;
        float y = player->y_pixel;

        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(x);
            yi = (int)roundf(y);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, YELLOW);
            x += ldx;
            y += ldy;
        }
    }
}*/
void fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i, j, xi, yi;
    float tmp, x, y, ldx, ldy;

    // INIT direction avant joueur
    ft_init_line(pos, array, player);
    for (i = 0; i < 80; i++)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
    }

    // Calcul direction perpendiculaire
    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;

    // Normalisation pour parcourir la perpendiculaire
    pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
    pos->dx /= pos->step;
    pos->dy /= pos->step;

    // === 1ère moitié de la FOV ===
    x = pos->x_pass;
    y = pos->y_pass;
    for (i = 0; i < 20; i++)
    {
        x += pos->dx;
        y += pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }
    }

    // === 2ème moitié de la FOV (inverse) ===
    x = pos->x_pass;
    y = pos->y_pass;
    for (i = 0; i < 20; i++)
    {
        x -= pos->dx;
        y -= pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
        }
    }
}

/*float *fov(struct s_trace_line *pos, struct s_array *array, struct s_position *player)
{
    int i, j, xi, yi;
    float tmp, x, y, ldx, ldy;
    float perpWallDist;
    float *ray_distances = malloc(sizeof(float) * 40);
    int ray_index;

    ray_index = 0;
    // INIT direction avant joueur
    ft_init_line(pos, array, player);
    for (i = 0; i < 80; i++)
    {
        pos->x_pass += pos->dx;
        pos->y_pass += pos->dy;
    }

    // Calcul direction perpendiculaire
    tmp = pos->dx;
    pos->dx = -pos->dy;
    pos->dy = tmp;

    // Normalisation pour parcourir la perpendiculaire
    pos->step = fmaxf(fabsf(pos->dx), fabsf(pos->dy));
    pos->dx /= pos->step;
    pos->dy /= pos->step;

    // === 1ère moitié de la FOV ===
    x = pos->x_pass;
    y = pos->y_pass;
    for (i = 0; i < 20; i++)
    {
        x += pos->dx;
        y += pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;
        float rx = player->x_pixel;
        float ry = player->y_pixel;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
            int mapX = (int)(player->x_pixel / 40);
            int mapY = (int)(player->y_pixel / 40);
            
            float rayDirX = ldx;
            float rayDirY = ldy;
            
            // Calcul des distances à parcourir dans X et Y
            float deltaDistX = fabsf(1.0f / rayDirX);
            float deltaDistY = fabsf(1.0f / rayDirY);
            
            int stepX, stepY;
            float sideDistX, sideDistY;
            
            // Initialisation des steps et sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (player->x_pixel - mapX * 40) / 40 * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = ((mapX + 1) * 40 - player->x_pixel) / 40 * deltaDistX;
            }
            
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (player->y_pixel - mapY * 40) / 40 * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = ((mapY + 1) * 40 - player->y_pixel) / 40 * deltaDistY;
            }
            
            // DDA
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
            
                // Test si on touche un mur
                if (mapY >= 0 && mapY < array->elmt.rows && mapX >= 0 && mapX < array->elmt.cols)
                {
                    if (array->line[mapY][mapX] == '1')
                        hit = 1;
                }
                else
                    break;
                if (hit && ray_index < 40)
                {
                    if (side == 0)
                        perpWallDist = (mapX - player->x_pixel / 40 + (1 - stepX) / 2) / rayDirX;
                    else
                        perpWallDist = (mapY - player->y_pixel / 40 + (1 - stepY) / 2) / rayDirY;
                    ray_distances[ray_index] = perpWallDist;
                    ray_index++;
                    break;
                }        
            }
        }
    }

    // === 2ème moitié de la FOV (inverse) ===
    x = pos->x_pass;
    y = pos->y_pass;
    for (i = 0; i < 20; i++)
    {
        x -= pos->dx;
        y -= pos->dy;
        ldx = x - player->x_pixel;
        ldy = y - player->y_pixel;

        pos->step = fmaxf(fabsf(ldx), fabsf(ldy));
        ldx /= pos->step;
        ldy /= pos->step;

        float rx = player->x_pixel;
        float ry = player->y_pixel;
        for (j = 0; j < 1000; j++)
        {
            xi = (int)roundf(rx);
            yi = (int)roundf(ry);
            if (xi < 0 || xi >= pos->width || yi < 0 || yi >= pos->height)
                break;
            if (array->line[yi / 40][xi / 40] == '1')
                break;
            ft_put_pixel(xi, yi, array, RED);
            rx += ldx;
            ry += ldy;
            int mapX = (int)(player->x_pixel / 40);
            int mapY = (int)(player->y_pixel / 40);
            
            float rayDirX = ldx;
            float rayDirY = ldy;
            
            // Calcul des distances à parcourir dans X et Y
            float deltaDistX = fabsf(1.0f / rayDirX);
            float deltaDistY = fabsf(1.0f / rayDirY);
            
            int stepX, stepY;
            float sideDistX, sideDistY;
            
            // Initialisation des steps et sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (player->x_pixel - mapX * 40) / 40 * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = ((mapX + 1) * 40 - player->x_pixel) / 40 * deltaDistX;
            }
            
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (player->y_pixel - mapY * 40) / 40 * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = ((mapY + 1) * 40 - player->y_pixel) / 40 * deltaDistY;
            }
            
            // DDA
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
            
                // Test si on touche un mur
                if (mapY >= 0 && mapY < array->elmt.rows && mapX >= 0 && mapX < array->elmt.cols)
                {
                    if (array->line[mapY][mapX] == '1')
                        hit = 1;
                }
                else
                    break;
                if (hit && ray_index < 40)
                {
                    if (side == 0)
                        perpWallDist = (mapX - player->x_pixel / 40 + (1 - stepX) / 2) / rayDirX;
                    else
                        perpWallDist = (mapY - player->y_pixel / 40 + (1 - stepY) / 2) / rayDirY;
                    ray_distances[ray_index] = perpWallDist;
                    ray_index++;
                    break;
                }                     
            }
        }
    }
    return(ray_distances);
}*/

void ft_dda_draw_ray(struct s_position *player, float rayDirX, float rayDirY, struct s_array *array)
{
    int mapX = (int)(player->x_pixel / 40);
    int mapY = (int)(player->y_pixel / 40);

    float deltaDistX = fabsf(1.0f / rayDirX);
    float deltaDistY = fabsf(1.0f / rayDirY);

    int stepX, stepY;
    float sideDistX, sideDistY;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (player->x_pixel - mapX * 40) / 40 * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = ((mapX + 1) * 40 - player->x_pixel) / 40 * deltaDistX;
    }

    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (player->y_pixel - mapY * 40) / 40 * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = ((mapY + 1) * 40 - player->y_pixel) / 40 * deltaDistY;
    }

    int hit = 0;
    //int side;

    float rayX = player->x_pixel;
    float rayY = player->y_pixel;

    // Boucle DDA
    while (!hit)
    {
        // Colorie la case traversée
        ft_put_pixel((int)rayX, (int)rayY, array, YELLOW);

        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            //side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            //side = 1;
        }

        // Mets à jour la position pixel du rayon
        rayX = mapX * 40 + 20; // centre de la case
        rayY = mapY * 40 + 20;

        if (mapX < 0 || mapY < 0 || mapX >= array->elmt.cols || mapY >= array->elmt.rows)
            break;

        if (array->line[mapY][mapX] == '1')
        {
            ft_put_pixel(rayX, rayY, array, RED); // mur touché
            hit = 1;
        }
    }
}

