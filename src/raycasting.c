/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 20:37:26 by aautin            #+#    #+#             */
/*   Updated: 2024/07/03 22:38:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <unistd.h>
#include <stdio.h>

#include "map.h"
#include "mlx.h"
#include "window.h"

#define ABS(value)	((value > 0) ? value : -value)
#define PLANE_LEN	0.66

typedef enum e_color
{
	RGB_Red = 0xff0000,
	RGB_Green = 0x00ff00,
	RGB_Blue = 0x0000ff,
	RGB_White = 0xffffff,
	RGB_Yellow = 0xffff00
}	t_color;

static int	rgbtoi(t_rgb *code)
{
	int	buffer = ((code->rCode&0x0ff)<<16)|((code->gCode&0x0ff)<<8)|(code->bCode&0x0ff);
	return buffer;
}

static void	putPixel(void *img, int x, int y, int color)
{
	int	bpp, line_len, endian;
	char *buffer = mlx_get_data_addr(img, &bpp, &line_len, &endian);

	*(int *)(buffer + y * line_len + x * (bpp / sizeof(int))) = color;
}

static void	verLine(void *img, int x, int drawStart, int drawEnd, t_formattedMap *map, int yWindowSize)
{
	for (int i = 0; i < drawStart; i++)
		putPixel(img, x, i, rgbtoi(&map->codes[C_IDENTIFY_INDEX]));
	while (drawEnd < yWindowSize)
		putPixel(img, x, drawEnd++, rgbtoi(&map->codes[F_IDENTIFY_INDEX]));
}

int	raycasting(void *mlx, t_window *window, t_formattedMap *map, t_player *player)
{
	void *img = mlx_new_image(mlx, window->xSize, window->ySize);

	double planeX = -player->yDirection, planeY = player->xDirection;
	for (int x = 0; x < window->xSize; x++)
    {
		//calculate ray position and direction
		double cameraX = (x * 2 / (double)(window->xSize)) - 1;
		double rayDirX = player->xDirection + planeX * cameraX;
		double rayDirY = player->yDirection + planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(player->xPosition);
		int mapY = (int)(player->yPosition);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : ABS(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : ABS(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->xPosition - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->xPosition) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->yPosition - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->yPosition) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
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

			//Check if ray has hit a wall
			if (map->area[mapY][mapX] == '1') hit = 1;
		}
		
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(window->ySize / perpWallDist);
		if (lineHeight < 0)
			lineHeight = INT_MAX;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + window->ySize / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + window->ySize / 2;
		if (drawEnd >= window->ySize) drawEnd = window->ySize - 1;

		//draw the pixels of the stripe as a vertical line
		verLine(img, x, drawStart, drawEnd, map, window->ySize);
	}
	mlx_put_image_to_window(mlx, window->obj, img, 0, 0);
	return SUCCESS;
}