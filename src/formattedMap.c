/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/20 00:16:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"

void	printIdentifiedMap(t_identifiedMap *identifiedMap)
{
	printf("NO path-texture: %s\n", identifiedMap->texturesFilename[NORTH_INDEX]);
	printf("SO path-texture: %s\n", identifiedMap->texturesFilename[SOUTH_INDEX]);
	printf("WE path-texture: %s\n", identifiedMap->texturesFilename[WEST_INDEX]);
	printf("EA path-texture: %s\n", identifiedMap->texturesFilename[EAST_INDEX]);
	printf("C_CODE: %s\n", identifiedMap->texturesFilename[C_CODE]);
	printf("F_CODE: %s\n", identifiedMap->texturesFilename[F_CODE]);
	printf("index of the first line of the map:%d\n", identifiedMap->mapStartIndex);
}

int	initMap(t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.mapStartIndex = NOT_FOUND;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printIdentifiedMap(&identifiedMap);
	(void) map;
	// ... here, have turn identifiedMap into formattedMap
	freeIdentifiedMap(&identifiedMap, COMPLETE);
	return EXIT_SUCCESS;
}
