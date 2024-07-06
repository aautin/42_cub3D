/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedLine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/02 20:37:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "map.h"

static int	getSurfaceIndex(char *identifier)
{
	const int	identifierLen = ft_strlen(identifier);

	if (identifierLen > 2)
		return NOT_FOUND;
	if (identifierLen == 1)
	{
		if (*identifier == 'C')
			return C_IDENTIFY_INDEX;
		return F_IDENTIFY_INDEX;
	}
	if (identifier[0] == 'N' && identifier[1] == 'O')
		return NO_IDENTIFY_INDEX;
	if (identifier[0] == 'S' && identifier[1] == 'O')
		return SO_IDENTIFY_INDEX;
	if (identifier[0] == 'W' && identifier[1] == 'E')
		return WE_IDENTIFY_INDEX;
	if (identifier[0] == 'E' && identifier[1] == 'A')
		return EA_IDENTIFY_INDEX;
	return NOT_FOUND;
}

int	isAreaBeginning(char *line)
{
	while (*line == ' ')
		line++;
	return line[0] != '\0' && ft_strchr("10", line[0]) != NULL;
}

static int	identifyComponents(t_identifiedMap *map, char **components, int lineIndex, int status)
{
	int		surfaceIndex;
	char	*surfaceComplement;

	if (!components[0] || !components[1] || components[2])
		surfaceIndex = NOT_FOUND;
	else
		surfaceIndex = getSurfaceIndex(components[0]);
	if (surfaceIndex == NOT_FOUND)
	{
		printf(ERROR_MSG "Line %d incorrect\n", lineIndex + 1);
		return NOT_FOUND;
	}
	surfaceComplement = ft_strdup(components[1]);
	if (surfaceComplement == NULL)
	{
		perror("identifyLine():ft_strdup()");
		return NOT_FOUND;
	}
	if (status & INDEX_TO_STATUS(surfaceIndex))
		free(map->surfaces[surfaceIndex]);
	map->surfaces[surfaceIndex] = surfaceComplement;
	return INDEX_TO_STATUS(surfaceIndex);
}

int	identifyLine(t_identifiedMap *map, char *line, int lineIndex, int status)
{
	if (line[0] == '\0')
		return 0;

	char **lineComponents = ft_split(line, ' ');
	if (lineComponents == NULL)
		return perror("identifyMap():ft_split()"), NOT_FOUND;
	int newStatus = identifyComponents(map, lineComponents, lineIndex, status);
	free_double_tab((void **) lineComponents, -1);
	return newStatus;
}
