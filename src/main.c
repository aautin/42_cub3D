/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 23:44:49 by aautin            #+#    #+#             */
/*   Updated: 2024/06/12 14:44:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "mlx_int.h"

#define DIR_LENGHT				-10
#define PLANE_LENGHT			10

#define DESTROY_WINDOW_EVENT	17
#define DESTROY_WINDOW_MASK		0

#define KEY_PRESSED_EVENT		2
#define KEY_PRESSED_MASK		(1L<<0)

#define ESC_KEYCODE				65307

int	keyHandlerEvent(int keycode, void *mlx)
{
	if (keycode == ESC_KEYCODE)
		mlx_loop_end(mlx);
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

	void *window = mlx_new_window(mlx, xScreenSize, yScreenSize, "cub3d: top_view");

	mlx_hook(window, DESTROY_WINDOW_EVENT, DESTROY_WINDOW_MASK, &mlx_loop_end, mlx);
	mlx_hook(window, KEY_PRESSED_EVENT, KEY_PRESSED_MASK, &keyHandlerEvent, mlx);
	mlx_loop(mlx);

	return 0;
}
