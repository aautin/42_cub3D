/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:41:18 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 22:53:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "X11_defines.h"
#include "libft.h"
#include "map.h"
#include "player.h"

static void	initPlayerDirection(t_player *player, char direction)
{
	player->xDirection = 0;
	player->yDirection = 0;
	if (direction == 'N')
		player->xDirection = -1;
	else if (direction == 'S')
		player->xDirection = 1;
	else if (direction == 'W')
		player->yDirection = -1;
	else if (direction == 'E')
		player->yDirection = 1;
}

void	initPlayer(t_player *player, t_formattedMap *map)
{
	int	rowI = 0;

	while (map->area[rowI] != NULL)
	{
		int	columnI = 0;
		while (columnI < map->xSize[rowI])
		{
			if (map->area[rowI][columnI ] == map->player)	
			{
				player->xPosition = columnI + 0.5;
				player->yPosition = rowI + 0.5;
				break ;
			}
			columnI++;
		}
		rowI++;
	}
	initPlayerDirection(player, map->player);
}

static void	keycodeToDirection(t_player *player, int keycode, double *xDirection, double *yDirection)
{
	if (keycode == XK_w)
	{
		*xDirection = player->xDirection;
		*yDirection = player->yDirection;
	}
	else if (keycode == XK_s)
	{
		*xDirection = -player->xDirection;
		*yDirection = -player->yDirection;
	}
	else if (keycode == XK_a)
	{
		*xDirection = player->yDirection;
		*yDirection = -player->xDirection;
	}
	else if (keycode == XK_d)
	{
		*xDirection = -player->yDirection;
		*yDirection = player->xDirection;
	}
}

int	makePlayerMove(char **area, t_player *player, int keycode)
{
	double	xDirection;
	double	yDirection;
	keycodeToDirection(player, keycode, &xDirection, &yDirection);

	double	xNewPosition;
	double	yNewPosition;
	int		move = FAILURE;

	xNewPosition = player->xPosition + xDirection;
	yNewPosition = player->yPosition + yDirection;
	if (area[(int)(player->yPosition)][(int)(xNewPosition)] != '\0'
		&& area[(int)(player->yPosition)][(int)(xNewPosition)] != '1')
	{
		player->xPosition = xNewPosition;
		move = SUCCESS;
	}
	if (area[(int)(yNewPosition)][(int)(player->xPosition)] != '\0'
		&& area[(int)(yNewPosition)][(int)(player->xPosition)] != '1')
	{
		player->yPosition = yNewPosition;
		move = SUCCESS;
	}
	return move;
}
