/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/22 20:47:21 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int	initFormattedMap(t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaStartIndex = NOT_FOUND;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printIdentifiedMap(&identifiedMap);
	(void) map;
	// ... here, have turn identifiedMap into formattedMap
	freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
	return EXIT_SUCCESS;
}
