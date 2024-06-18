/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:34:27 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 03:25:00 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"

#include "window.h"

int	initWindow(t_window *window, void *mlx, int xSize, int ySize)
{
	
	window->obj = mlx_new_window(mlx, xSize, ySize, "cub3D");
	if (window->obj == NULL)
	{
		perror("initWindow():mlx_new_window()");
		return EXIT_FAILURE;
	}
	window->xSize = xSize;
	window->ySize = ySize;
	return EXIT_SUCCESS;
}
