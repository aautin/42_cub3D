/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/15 23:52:29 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extended.h"
#include "mlx.h"
#include "mlx_int.h"

#define DIR_LENGHT				1
#define PLANE_LENGHT			2 * DIR_LENGHT
// here "2 * DIR_LENGHT" sets a 90' FOV

#define DESTROY_WINDOW_EVENT	17
#define DESTROY_WINDOW_MASK		0

#define KEY_PRESSED_EVENT		2
#define KEY_PRESSED_MASK		(1L<<0)

#define ESC_KEYCODE				65307

#define	A_KEYCODE_LEFT			97
#define	D_KEYCODE_RIGHT			100
#define	S_KEYCODE_DOWN			115
#define	W_KEYCODE_UP			119

typedef struct s_windowConfig {
	void *obj;
	int xSize;
	int ySize;
}	t_windowConfig;
void	windowConfigInit(t_windowConfig *config, void *obj, int xSize, int ySize)
{
	config->obj = obj;
	config->xSize = xSize;
	config->ySize = ySize;
}

typedef struct s_player {
	int xPosition;
	int yPosition;
	int directionIndex;
}	t_player;
void	playerInit(t_player *player, int xPosition, int yPosition, int directionIndex)
{
	player->xPosition = xPosition;
	player->yPosition = yPosition;
	player->directionIndex = directionIndex;
}

typedef struct s_raycastingConfig {
	int raysNumber;
	char directions[16];
}	t_raycastConfig;
void	initRaycastConfig(t_raycastConfig *raycast, int raysNumber, char directions[16])
{
	raycast->raysNumber = raysNumber;
	raycast->directions = directions;
}

void	modifyPlayerPosition(int keycode, void **params)
{
}

int	keyHandlerEvent(int keycode, void **params)
{

	if (keycode == ESC_KEYCODE)
		mlx_loop_end(params[MLX_INDEX]);
	else
	{
		modifyPlayerPosition(keycode, params);
		ft_printf("player's position: %dx*%dy\n",
				* (int *)params[PLAYER_XPOS_INDEX], * (int *)params[PLAYER_YPOS_INDEX]);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	void *mlx = mlx_init();
	if (mlx == NULL)
		return 1;

	int	xScreenSize, yScreenSize;
	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize <= DIR_LENGHT * 2 || yScreenSize <= DIR_LENGHT * 2)
		return 0;

	int	xPlayerPosition = , yPlayerPosition = yScreenSize / 2;

	void *window = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3d: top_view");

	t_windowConfig config;
	windowConfigInit(&config, window, xScreenSize, yScreenSize);

	t_player player;
	playerInit(&player, config.xSize / 2, config.ySize / 2, 0);

	
	void *params[3];
	params[MLX_INDEX] = mlx;
	params[PLAYER_XPOS_INDEX] = &xPlayerPosition;
	params[PLAYER_YPOS_INDEX] = &yPlayerPosition;
	params[WINDOW_XSIZE_INDEX] = &xScreenSize;
	params[WINDOW_YSIZE_INDEX] = &yScreenSize;

	mlx_hook(window, DESTROY_WINDOW_EVENT, DESTROY_WINDOW_MASK, &mlx_loop_end, params);
	mlx_hook(window, KEY_PRESSED_EVENT, KEY_PRESSED_MASK, &keyHandlerEvent, params);

	mlx_loop(mlx);

	return 0;
}
