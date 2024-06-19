/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/19 22:40:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"

int	initMap(t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.mapStartIndex = NOT_FOUND;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	(void) map;
	// ... here, have turn identifiedMap into formattedMap
	freeIdentifiedMap(&identifiedMap, COMPLETE);
	return EXIT_FAILURE;
}
