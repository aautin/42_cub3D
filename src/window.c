/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:34:27 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 20:39:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "mlx.h"
#include "window.h"

#define WINDOW_MIN_SIZE 480

int	initWindow(t_window *window, void *mlx)
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
