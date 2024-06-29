/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:41:18 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/29 19:08:39 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			if (map->area[rowI] == map->player)	
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
