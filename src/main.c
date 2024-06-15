/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/15 23:51:56 by aautin           ###   ########.fr       */
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

#define	MLX_INDEX				0
#define	PLAYER_XPOS_INDEX		1
#define	PLAYER_YPOS_INDEX		2

#define WINDOW_XSIZE_INDEX		3
#define WINDOW_YSIZE_INDEX		4

void	modifyPlayerPosition(int keycode, void **params)
{
	int *xPlayerPosition = params[PLAYER_XPOS_INDEX];
	int *yPlayerPosition = params[PLAYER_YPOS_INDEX];
	int *xScreenSize = params[WINDOW_XSIZE_INDEX];
	int *yScreenSize = params[WINDOW_YSIZE_INDEX];

	*xPlayerPosition -= (keycode == A_KEYCODE && *xPlayerPosition > 0);
	*xPlayerPosition += (keycode == D_KEYCODE && *xPlayerPosition < *xScreenSize);
	*yPlayerPosition -= (keycode == W_KEYCODE && *yPlayerPosition > 0);
	*yPlayerPosition += (keycode == S_KEYCODE && *yPlayerPosition < *yScreenSize);
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
		return (1);

	int	xScreenSize, yScreenSize;
	mlx_get_screen_size(mlx, &xScreenSize, &yScreenSize);
	if (xScreenSize <= DIR_LENGHT * 2 || yScreenSize <= DIR_LENGHT * 2)
		return 0;

	int	xPlayerPosition = xScreenSize / 2, yPlayerPosition = yScreenSize / 2;

	void *window = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3d: top_view");

	void *params[5];
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
