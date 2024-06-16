/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:34:27 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/16 23:36:23 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void	initWindow(t_window *window, void *obj, int xSize, int ySize)
{
	window->obj = obj;
	window->xSize = xSize;
	window->ySize = ySize;
}
