/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:34:27 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 23:45:19 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "X11_defines.h"
#include "player.h"
#include "libft.h"
#include "map.h"
#include "mlx.h"
#include "window.h"

#define MLX_INDEX		0
#define MAP_INDEX		1
#define PLAYER_INDEX	2

#define WINDOW_MIN_SIZE 480

static int keyPressHandler(int keycode, void **param)
{
	if (keycode == XK_Escape)
		mlx_loop_end(param[MLX_INDEX]);
	else if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		((t_player *)(param[PLAYER_INDEX]))->isMoving = keycode;
	return SUCCESS;
}

static int keyReleaseHandler(int keycode, t_player *player)
{
	if (keycode == XK_w || keycode == XK_s
		|| keycode == XK_a || keycode == XK_d)
		player->isMoving = FALSE;
	return SUCCESS;
}

void	initWindowHooks(void *mlx, t_window *window, t_formattedMap *map, t_player *player)
{
	void *param[3] = {mlx, map, player};
	mlx_hook(window, KeyPress, KeyPressMask, &keyPressHandler, param);
	mlx_hook(window, KeyRelease, KeyReleaseMask, &keyReleaseHandler, param);
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
