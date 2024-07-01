/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 20:17:52 by aautin           ###   ########.fr       */
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

int	initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaIndex = NOT_FOUND;
	if (initIdentification(&identifiedMap, mapFileName, &map->area) == EXIT_FAILURE)
		return EXIT_FAILURE;
	if (initCodes(map->codes, identifiedMap.surfaces) == EXIT_FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	if (initTextureObjs(mlx, map, &identifiedMap) == EXIT_FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	if (initArea(map) == EXIT_FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeTextureObjs(mlx, map->textureObjs);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	return freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS), EXIT_SUCCESS;
}
