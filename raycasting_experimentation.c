#include <limits.h>
#include <stdlib.h>

#include "mlx/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#define ABS(value) ((value > 0) ? value : -value)

typedef enum e_color
{
	RGB_Red = 0xff0000,
	RGB_Green = 0x00ff00,
	RGB_Blue = 0x0000ff,
	RGB_White = 0xffffff,
	RGB_Yellow = 0xffff00
}	t_color;

#define FLOOR_COLOR 0x123456
#define CEIL_COLOR 0x789abc

int worldMap[mapWidth][mapHeight]=
{
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	putPixel(void *img, int x, int y, int color)
{
	int	bpp, line_len, endian;
	char *buffer = mlx_get_data_addr(img, &bpp, &line_len, &endian);

	*(int *)(buffer + y * line_len + x * (bpp / sizeof(int))) = color;
}

void	verLine(void *img, int x, int drawStart, int drawEnd, int color)
{
	for (int i = 0; i < drawStart; i++)
		putPixel(img, x, i, CEIL_COLOR);
	while (drawStart <= drawEnd)
		putPixel(img, x, drawStart++, color);
	while (drawEnd < screenHeight)
		putPixel(img, x, drawEnd++, FLOOR_COLOR);
}


int main()
{
	void *mlxPtr = mlx_init();
	void *window = mlx_new_window(mlxPtr, screenWidth, screenHeight, "test");
	void *img = mlx_new_image(mlxPtr, screenWidth, screenHeight);

	double posX = 14, posY = 10;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	for(int x = 0; x < screenWidth; x++)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)(screenWidth) - 1; //x-coordinate in camera space -> [-1, 1]
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;

		//which box of the map we're in
		int mapX = (int)(posX);
		int mapY = (int)(posY);

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
		sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
			if (worldMap[mapX][mapY] > 0) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)

		if (side == 0) perpWallDist = (sideDistX - deltaDistX);
		else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(screenHeight / perpWallDist);
		if (lineHeight < 0)
			lineHeight = INT_MAX;

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;
		//choose wall color
		t_color color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = RGB_Red;  break; //red
			case 2:  color = RGB_Green;  break; //green
			case 3:  color = RGB_Blue;   break; //blue
			case 4:  color = RGB_White;  break; //white
			default: color = RGB_Yellow; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color / 2;}

		//draw the pixels of the stripe as a vertical line
		verLine(img, x, drawStart, drawEnd, color);
	}
	mlx_put_image_to_window(mlxPtr, window, img, 0, 0);
	while (1);

	return EXIT_SUCCESS;
}