/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedArea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:24:21 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 17:31:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "map.h"
#include "player.h"

static int	check_player(char **area)
{
	char	player;
	int		x;
	int		y;

	player = 0;
	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (area[y][x] != '\0')
		{
			if (ft_strchr("NSWE", area[y][x]) != NULL && player)
				return (printf(ERROR_MSG "Map has several players\n"), FAILURE);
			else if (ft_strchr("NSWE", area[y][x]))
				player = area[y][x];
			x++;
		}
		y++;
	}
	if (!player)
	{
		printf(ERROR_MSG "Map has no player\n");
		return FAILURE;
	}
	return SUCCESS;
}

static int	floodchar(int *xSize, char **area, int lineI, int colI)
{
	int	status = FAILURE;

	if (lineI - 1 < 0 || xSize[lineI - 1] - 1 < colI 
		|| area[lineI + 1] == NULL || xSize[lineI + 1] - 1 < colI
		|| colI - 1 < 0 || area[lineI][colI + 1] == '\0')
		return NOT_FOUND;
	for (int step = -1; step <= 1; step += 2)
	{
		if (area[lineI + step][colI] && ft_strchr("0 ", area[lineI + step][colI]) != NULL)
		{
			status = SUCCESS;
			area[lineI + step][colI] = 'T';
		}
	}
	for (int step = -1; step <= 1; step += 2)
	{
		if (area[lineI + step][colI] && ft_strchr("0 ", area[lineI][colI + step]) != NULL)
		{
			status = SUCCESS;
			area[lineI][colI + step] = 'T';
		}
	}
	return status;
}

static int	floodline(t_map *map, int lineI, int *expansion, int *xSize)
{
	int	colI = 0;

	while (map->area[lineI][colI] != '\0')
	{
		if (ft_strchr("NSWET", map->area[lineI][colI]) != NULL)
		{
			int	flood_status = floodchar(xSize, map->area, lineI, colI);
			if (flood_status == NOT_FOUND)
			{
				printf(ERROR_MSG "Map isn't closed\n");
				return FAILURE;
			}
			if (flood_status == EXIT_SUCCESS)
				*expansion = TRUE;
		}
		else if (ft_strchr("10 ", map->area[lineI][colI]) == NULL)
		{
			printf(ERROR_MSG "Map has wrong chars\n");
			return FAILURE;
		}
		colI++;
	}
	return SUCCESS;
}

static int	floodfill(t_map *map, int *xSize)
{
	int expansion = TRUE;

	while (expansion == TRUE)
	{
		expansion = FALSE;
		int	i = 0;
		while (map->area[i] != NULL)
		{
			if (floodline(map, i, &expansion, xSize) == FAILURE)
				return FAILURE;
			i++;
		}
	}
	return SUCCESS;
}

int	initArea(t_map *map, t_player *player)
{
	int *xSize = initAreaxSize(map->area);
	if (xSize == NULL)
		return EXIT_FAILURE;
	if (floodfill(map, xSize) == SUCCESS && check_player(map->area) == SUCCESS)
	{
		init_player(player, map->area);
		cleanArea(map->area, xSize);
		free(xSize);
		return SUCCESS;
	}
	free(xSize);
	return FAILURE;
}
