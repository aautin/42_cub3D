/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/18 02:12:56 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mlx.h"
#include "mlx_int.h"

#include "hook.h"
#include "keycode.h"
#include "map.h"
#include "player.h"
#include "window.h"

#define STEP_LENGHT		0.1
#define DIR_LENGHT		1
#define PLANE_LENGHT	2 * DIR_LENGHT
// here "2 * DIR_LENGHT" sets a 90' FOV

static void	initKeyHandlerParam(t_keyHandlerParam *param, t_window *window, t_map *map, t_player *player, void *mlx)
{
	param->window = window;
	param->player = player;
	param->map = map;
	param->mlx = mlx;
}

int	isKeycodeMakingPlayerMove(int keycode, t_map *map, t_player *player)
{
	(void) map;
	(void) player;
	switch (keycode)
	{
		case A_KEYCODE_LEFT :
			return 1;
		case D_KEYCODE_RIGHT :
			return 1;
		case W_KEYCODE_UP :
			return 1;
		case S_KEYCODE_DOWN :
			return 1;
		default :
			return 0;
	}
}

void	modifyPlayerPosition(int keycode, t_player *player)
{
	(void) player;
	switch (keycode)
	{
		case A_KEYCODE_LEFT :
			ft_printf("LEFT->");
			break;
		case D_KEYCODE_RIGHT :
			ft_printf("RIGHT->");
			break;
		case W_KEYCODE_UP :
			ft_printf("UP->");
			break;
		case S_KEYCODE_DOWN :
			ft_printf("DOWN->");
			break;
		default :
			break;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	void *mlx = mlx_init();
	if (mlx == NULL)
		return 1;

	int	xScreenSize, yScreenSize;
	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize <= DIR_LENGHT * 2 || yScreenSize <= DIR_LENGHT * 2)
		return 0;

	void *windowObj = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3D");

	t_window window;
	initWindow(&window, windowObj, xScreenSize, yScreenSize);

	t_map map;
	initMap(&map, argv[1]);

	t_player player;
	initPlayer(&player, &map);
	
	t_keyHandlerParam keyHandlerParam;
	initKeyHandlerParam(&keyHandlerParam, &window, &map, &player, mlx);
	setWindowHooks(&keyHandlerParam);
	mlx_loop(mlx);

	return 0;
}
