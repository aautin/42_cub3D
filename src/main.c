/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/18 11:30:48 by alexandre        ###   ########.fr       */
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

static void	initKeyHandlerParam(t_keyHandlerParam *param, t_window *window, t_formattedMap *map, t_player *player, void *mlx)
{
	param->window = window;
	param->player = player;
	param->map = map;
	param->mlx = mlx;
}

int	isKeycodeMakingPlayerMove(int keycode, t_formattedMap *map, t_player *player)
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
	{
		perror("main():mlx_init()");
		return EXIT_FAILURE;
	}

	int	xScreenSize, yScreenSize;
	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize <= DIR_LENGHT * 2 || yScreenSize <= DIR_LENGHT * 2)
	{
		ft_printf("Screen size isn't adapted for this program.\n");
		return EXIT_SUCCESS;
	}

	t_formattedMap map;
	if (initMap(&map, argv[1]) == EXIT_FAILURE)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return EXIT_FAILURE;
	}

	t_window window;
	if (initWindow(&window, mlx, xScreenSize, yScreenSize) == EXIT_FAILURE)
	{
		// free map
		mlx_destroy_display(mlx);
		return EXIT_FAILURE;
	}

	t_player player;
	initPlayer(&player, &map);
	
	t_keyHandlerParam keyHandlerParam;
	initKeyHandlerParam(&keyHandlerParam, &window, &map, &player, mlx);
	setWindowHooks(&keyHandlerParam);
	mlx_loop(mlx);

	return EXIT_SUCCESS;
}
