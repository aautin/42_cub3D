/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:34:27 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/03 20:07:24 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "X11_defines.h"
#include "player.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "window.h"

static int keyPressHandler(int keycode, t_handlerParam *param)
{
	if (keycode == XK_Escape)
		mlx_loop_end(param->mlx);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		param->player->isMoving = keycode;
	return SUCCESS;
}

static int keyReleaseHandler(int keycode, t_player *player)
{
	if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		player->isMoving = FALSE;
	return SUCCESS;
}

static int	gameEventsHandler(t_handlerParam *param)
{
	int	mustUpdateWindow = FALSE;

	if (param->player->isMoving)
	{
		if (makePlayerMove(param->map->area, param->player, param->player->isMoving) == SUCCESS)
			mustUpdateWindow = TRUE;
	}

	if (mustUpdateWindow == TRUE)
	{
		if (raycasting() == FAILURE)
		{
			mlx_loop_end(param->mlx);
			return FAILURE;
		}
	}
	return SUCCESS;
}

void	initWindowHooks(t_handlerParam *param)
{
	mlx_hook(param->window->obj, KeyPress, KeyPressMask, &keyPressHandler, param);
	mlx_hook(param->window->obj, KeyRelease, KeyReleaseMask, &keyReleaseHandler, param->player);
	mlx_loop_hook(param->mlx, &gameEventsHandler, param);
}

int	initWindow(void *mlx, t_window *window)
{
	int	xScreenSize, yScreenSize;

	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize < WINDOW_MIN_SIZE || yScreenSize < WINDOW_MIN_SIZE)
	{
		printf("Screen size isn't adapted for this program.\n");
		return FAILURE;
	}

	window->obj = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3D");
	if (window->obj == NULL)
	{
		perror("initWindow():mlx_new_window()");
		return FAILURE;
	}
	window->xSize = xScreenSize;
	window->ySize = yScreenSize;
	return SUCCESS;
}
