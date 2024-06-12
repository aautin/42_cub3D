/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/13 00:19:00 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_extended.h"
#include "mlx.h"
#include "mlx_int.h"

#define DIR_LENGHT				-10
#define PLANE_LENGHT			10

#define DESTROY_WINDOW_EVENT	17
#define DESTROY_WINDOW_MASK		0

#define KEY_PRESSED_EVENT		2
#define KEY_PRESSED_MASK		(1L<<0)

#define ESC_KEYCODE				65307

#define	A_KEYCODE				97
#define	D_KEYCODE				100
#define	S_KEYCODE				115
#define	W_KEYCODE				119

#define	MLX_INDEX				0
#define	PLAYER_XPOS_INDEX		1
#define	PLAYER_YPOS_INDEX		2

#define SCREEN_XSIZE_INDEX		3
#define SCREEN_YSIZE_INDEX		4

void	modifyPlayerPos(int keycode, void **params)
{
	int *xPlayerPos = params[PLAYER_XPOS_INDEX];
	int *yPlayerPos = params[PLAYER_YPOS_INDEX];
	int *xScreenSize = params[SCREEN_XSIZE_INDEX];
	int *yScreenSize = params[SCREEN_YSIZE_INDEX];

	*xPlayerPos -= (keycode == A_KEYCODE && *xPlayerPos > 0);
	*xPlayerPos += (keycode == D_KEYCODE && *xPlayerPos < *xScreenSize);
	*yPlayerPos -= (keycode == W_KEYCODE && *yPlayerPos > 0);
	*yPlayerPos += (keycode == S_KEYCODE && *yPlayerPos < *yScreenSize);
}

int	keyHandlerEvent(int keycode, void **params)
{

	if (keycode == ESC_KEYCODE)
		mlx_loop_end(params[MLX_INDEX]);
	else
	{
		modifyPlayerPos(keycode, params);
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

	int	xPlayerPos = xScreenSize / 2, yPlayerPos = yScreenSize / 2;

	void *window = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3d: top_view");

	void *params[5];
	params[MLX_INDEX] = mlx;
	params[PLAYER_XPOS_INDEX] = &xPlayerPos;
	params[PLAYER_YPOS_INDEX] = &yPlayerPos;
	params[SCREEN_XSIZE_INDEX] = &xScreenSize;
	params[SCREEN_YSIZE_INDEX] = &yScreenSize;

	mlx_hook(window, DESTROY_WINDOW_EVENT, DESTROY_WINDOW_MASK, &mlx_loop_end, params);
	mlx_hook(window, KEY_PRESSED_EVENT, KEY_PRESSED_MASK, &keyHandlerEvent, params);

	mlx_loop(mlx);

	return 0;
}
