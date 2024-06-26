/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 01:07:10 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 11:30:48 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "mlx_int.h"
#include "mlx.h"

#include "hook.h"
#include "keycode.h"
#include "map.h"
#include "player.h"
#include "window.h"


int		isKeycodeMakingPlayerMove(int keycode, t_formattedMap *map, t_player *player);
void	modifyPlayerPosition(int keycode, t_player *player);

static int	keyHandler(int keycode, t_keyHandlerParam *param)
{
	if (keycode == ESC_KEYCODE)
		mlx_loop_end(param->mlx);
	else if (isKeycodeMakingPlayerMove(keycode, param->map, param->player))
	{
		modifyPlayerPosition(keycode, param->player);
		ft_printf("new position: %d.%dx*%d.%dy\n",	param->player->xPosition,
													(int)(param->player->xCasePosition * 10),
													param->player->yPosition,
													(int)(param->player->yCasePosition * 10));
	}
	return 0;
}

void    setWindowHooks(t_keyHandlerParam *param)
{
	mlx_hook(param->window->obj, KEY_PRESSED_EVENT, KEY_PRESSED_MASK, &keyHandler, param);
	mlx_hook(param->window->obj, DESTROY_WINDOW_EVENT, DESTROY_WINDOW_MASK, &mlx_loop_end, param->mlx);
}
