/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:41:18 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 20:07:22 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "map.h"
#include "player.h"

static void	initPlayerDirection(t_player *player, char direction)
{
	player->xDirection = 0;
	player->yDirection = 0;
	if (direction == NORTH)
		player->xDirection = -1;
	else if (direction == SOUTH)
		player->xDirection = 1;
	else if (direction == WEST)
		player->yDirection = -1;
	else if (direction == EAST)
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
				player->xPosition = columnI;
				player->yPosition = rowI;
				break ;
			}
			columnI++;
		}
		rowI++;
	}
	initPlayerDirection(player, map->player);
	player->xCasePosition = 0.5;
	player->yCasePosition = 0.5;
}
