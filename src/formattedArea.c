/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedArea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:24:21 by aautin            #+#    #+#             */
/*   Updated: 2024/06/26 20:43:18 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

#include "map.h"

static int	initPlayer(char currentPosition, char *player)
{
	if (ft_strchr("NSWE", currentPosition) != NULL)
	{
		if (*player)
		{
			printf(ERROR_MSG "Map has several players\n");
			return EXIT_FAILURE;		
		}
		*player = currentPosition;
	}
	return EXIT_SUCCESS;
}

static int	floodchar(int *xSize, char **area, int lineI, int colI)
{
	int	status = EXIT_FAILURE;

	if (lineI - 1 < 0 || xSize[lineI - 1] - 1 < colI 
		|| area[lineI + 1] == NULL || xSize[lineI + 1] - 1 < colI
		|| colI - 1 < 0 || area[lineI][colI + 1] == '\0')
		return NOT_FOUND;
	for (int step = -1; step <= 1; step += 2)
	{
		if (area[lineI + step][colI] && ft_strchr("0 ", area[lineI + step][colI]) != NULL)
		{
			status = EXIT_SUCCESS;
			area[lineI + step][colI] = 'T';
		}
	}
	for (int step = -1; step <= 1; step += 2)
	{
		if (area[lineI + step][colI] && ft_strchr("0 ", area[lineI][colI + step]) != NULL)
		{
			status = EXIT_SUCCESS;
			area[lineI][colI + step] = 'T';
		}
	}
	return status;
}

static int	floodline(t_formattedMap *map, char **area, int lineI, int *expansion)
{
	int	colI = 0;

	while (area[lineI][colI] != '\0')
	{
		if (initPlayer(area[lineI][colI], &map->player) == EXIT_FAILURE)
			return EXIT_FAILURE;
		if (ft_strchr("NSWET", area[lineI][colI]) != NULL)
		{
			int	flood_status = floodchar(map->xSize, area, lineI, colI);
			if (flood_status == NOT_FOUND)
			{
				printf(ERROR_MSG "Map isn't closed\n");
				return EXIT_FAILURE;
			}
			if (flood_status == EXIT_SUCCESS)
				*expansion = TRUE;
		}
		else if (ft_strchr("10 ", area[lineI][colI]) == NULL)
		{
			printf(ERROR_MSG "Map has wrong chars\n");
			return EXIT_FAILURE;
		}
		colI++;
	}
	return EXIT_SUCCESS;
}

static int	floodfill(t_formattedMap *map)
{
	int expansion = TRUE;
	while (expansion == TRUE)
	{
		map->player = 0;
		expansion = FALSE;
		int	i = 0;
		while (map->area[i] != NULL)
		{
			if (floodline(map, map->area, i, &expansion) == EXIT_FAILURE)
				return EXIT_FAILURE;
			i++;
		}
		if (!map->player)
		{
			printf(ERROR_MSG "Map has no player\n");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int	initArea(t_formattedMap *map)
{
	map->xSize = initAreaxSize(map->area);
	if (map->xSize == NULL)
		return EXIT_FAILURE;

	int	status = floodfill(map);
	if (status == EXIT_FAILURE)
		free(map->xSize);

	return status;
}