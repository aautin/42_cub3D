/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/23 19:37:44 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "mlx.h"
#include "map.h"

void	printIdentifiedMap(t_identifiedMap *identifiedMap)
{
	printf("C_CODE: %s\n", identifiedMap->surfaces[C_INDEX]);
	printf("F_CODE: %s\n", identifiedMap->surfaces[F_INDEX]);
	printf("NO path-texture: %s\n", identifiedMap->surfaces[NORTH_INDEX]);
	printf("SO path-texture: %s\n", identifiedMap->surfaces[SOUTH_INDEX]);
	printf("WE path-texture: %s\n", identifiedMap->surfaces[WEST_INDEX]);
	printf("EA path-texture: %s\n", identifiedMap->surfaces[EAST_INDEX]);
	printf("index of the first line of the map:%d\n", identifiedMap->areaIndex);
}

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
	printIdentifiedMap(&identifiedMap);
	if (checkArea(map) == EXIT_FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeTextureObjs(mlx, map->textureObjs);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
	return EXIT_SUCCESS;
}
