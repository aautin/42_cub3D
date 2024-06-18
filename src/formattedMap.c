/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 11:30:48 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "map.h"

int	initMap(t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	(void) map;
	// ...
	return EXIT_FAILURE;
}
