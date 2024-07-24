/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:31:21 by aautin            #+#    #+#             */
/*   Updated: 2024/07/24 01:25:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "player.h"
#include "map.h"

static void	init_player_from_direction(t_player *player, char direction)
{
	player->dirx = 0;
	player->diry = 0;
	player->planex = 0;
	player->planey = 0;
	if (direction == 'N')
	{
		player->diry = -1;
		player->planex = 0.66;
	}
	else if (direction == 'S')
	{
		player->diry = 1;
		player->planex = -0.66;
	}
	else if (direction == 'W')
	{
		player->dirx = -1;
		player->planey = -0.66;
	}
	else if (direction == 'E')
	{
		player->dirx = 1;
		player->planey = 0.66;
	}
}

void	init_player(t_player *player, char **area)
{
	int	y;
	int	x;

	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (area[y][x] != '\0')
		{
			if (ft_strchr("NSWE", area[y][x]) != NULL)
			{
				player->x = x;
				player->y = y;
				init_player_from_direction(player, area[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
