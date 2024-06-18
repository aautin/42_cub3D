/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:41:18 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 02:09:10 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "map.h"
#include "player.h"

static void	initPlayerPosition(t_player *player, t_map *map)
{
	int	rowI = 0;
	while (rowI < map->ySize)
	{
		int	columnI = 0;
		while (columnI < map->xSize)
		{
			if (ft_strchr("01", map->area[rowI][columnI]) == NULL)	
			{
				player->xPosition = columnI;
				player->yPosition = rowI;
				return ;
			}
			columnI++;
		}
		rowI++;
	}
}

static void	initPlayerDirection(t_player *player, int direction)
{
	if (direction == NORTH)
	{
		player->xDirection = -1;
		player->yDirection = 0;
	}
	else if (direction == SOUTH)
	{
		player->xDirection = 1;
		player->yDirection = 0;
	}
	else if (direction == WEST)
	{
		player->xDirection = 0;
		player->yDirection = -1;
	}
	else if (direction == EAST)
	{
		player->xDirection = 0;
		player->yDirection = 1;
	}
}

void	initPlayer(t_player *player, t_map *map)
{
	initPlayerPosition(player, map);
	initPlayerDirection(player, map->area[player->yPosition][player->xPosition]);
	player->xCasePosition = 0.5;
	player->yCasePosition = 0.5;
}
