/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 20:48:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"

void	freeTextureObjs(void *mlx, void **textureObjs)
{
	int	i = NORTH_INDEX;

	while (i <= EAST_INDEX)
	{
		mlx_destroy_image(mlx, textureObjs[i]);
		i++;
	}
}

void	cleanArea(char **area, int *xSize)
{
	int	x, y;

	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (x < xSize[y])
		{
			if (ft_strchr(" TNSWE", area[y][x]) != NULL)
				area[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	freeFormattedMap(void *mlx, t_formattedMap *map)
{
	free_double_tab((void **) map->area, -1);
	freeTextureObjs(mlx, map->textureObjs);
	free(map->xSize);
}

int	initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaIndex = NOT_FOUND;
	if (initIdentification(&identifiedMap, mapFileName, &map->area) == FAILURE)
		return FAILURE;
	if (initCodes(map->codes, identifiedMap.surfaces) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	if (initTextureObjs(mlx, map, &identifiedMap) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	if (initArea(map) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeTextureObjs(mlx, map->textureObjs);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	return freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS), EXIT_SUCCESS;
}
