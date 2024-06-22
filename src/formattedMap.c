/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/22 21:53:51 by aautin           ###   ########.fr       */
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
	printf("index of the first line of the map:%d\n", identifiedMap->areaStartIndex);
}

int	createTextureObjs(void *mlx, t_formattedMap *formatMap, t_identifiedMap *identMap)
{
	void	*newImage;
	int 	i = 0;

	while (i < EAST_INDEX)
	{
		if (access(identMap->surfaces[i], F_OK) == -1)
		{
			printf("%sCan't open or read %s\n", ERROR_MSG,
				identMap->surfaces[i]);
			return EXIT_FAILURE;
		}
		i++;
	}
	i = 0;
	while (i < EAST_INDEX)
	{
		newImage = mlx_xpm_file_to_image(mlx, identMap->surfaces[i],
			&formatMap->texturesObjWidth[i], &formatMap->texturesObjHeight[i]);
		if (newImage == NULL)
		{
			printf("%s An error occured when turning %s xmp to image\n",
				ERROR_MSG, identMap->surfaces[i]);
		}
		i++;
	}
	return EXIT_SUCCESS;
}

int	initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaStartIndex = NOT_FOUND;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printIdentifiedMap(&identifiedMap);
	if (createTextureObjs(mlx, map, &identifiedMap) == EXIT_FAILURE)
	{
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	// .. here have to parse map area
	freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
	return EXIT_SUCCESS;
}
