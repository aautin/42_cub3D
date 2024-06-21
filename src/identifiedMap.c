/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/21 23:53:14 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

#include "ft_printf.h"

void	freeIdentifiedMap(t_identifiedMap *map, int status)
{
	int	i = 0;

	while (i <= F_INDEX)
	{
		if (status & INDEX_TO_STATUS(i))
			free(map->surfaces[i]);
		i++;
	}
}

static int	initDataBlock(char *dataBlock[], int fd)
{
	t_list *dataElements = NULL;

	*dataBlock = get_next_line(fd);
	while (*dataBlock != NULL)
	{
		t_list *newElement = ft_lstnew(*dataBlock);
		if (newElement == NULL)
		{
			perror("initMapData():ft_lstnew()");
			free(*dataBlock);
			ft_lstclear(&dataElements, &free);
			return EXIT_FAILURE;
		}
		ft_lstadd_back(&dataElements, newElement);
		*dataBlock = get_next_line(fd);
	}

	*dataBlock = lsttostr(dataElements);
	ft_lstclear(&dataElements, &free);
	if (*dataBlock == NULL)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

static int	getSurfaceIndex(char *identifier)
{
	const int	identifierLen = ft_strlen(identifier);

	if (identifierLen > 2)
		return NOT_FOUND;
	if (identifierLen == 1)
	{
		if (*identifier == 'C')
			return C_INDEX;
		return F_INDEX;
	}
	if (*identifier == 'N')
		return NORTH_INDEX;
	if (*identifier == 'S')
		return SOUTH_INDEX;
	if (*identifier == 'W')
		return WEST_INDEX;
	return EAST_INDEX;
}

static int	identifyLine(t_identifiedMap *map, char **components, int lineIndex, int currStatus)
{
	int		surfaceIndex;
	char	*surfaceComplement;

	if (!components[0] || !components[1] || components[2])
		surfaceIndex = NOT_FOUND;
	else
		surfaceIndex = getSurfaceIndex(components[0]);
	if (surfaceIndex == NOT_FOUND)
	{
		printf("%sLine %d incorrect\n", ERROR_MSG, lineIndex);
		return NOT_FOUND;
	}
	surfaceComplement = ft_strdup(components[1]);
	if (surfaceComplement == NULL)
	{
		perror("identifyLine():ft_strdup()");
		return NOT_FOUND;
	}
	if (currStatus & INDEX_TO_STATUS(surfaceIndex))
		free(map->surfaces[surfaceIndex]);
	map->surfaces[surfaceIndex] = surfaceComplement;
	return INDEX_TO_STATUS(surfaceIndex);
}

static int	isAreaBeginning(char *line)
{
	while (*line == ' ')
		line++;
	return ft_strchr("10", line[0]) != NULL;
}

static int	identifyMap(t_identifiedMap *map, char **lines)
{
	int	newStatus;
	int	status = 0;
	int	i = 0;

	while (lines[i] != NULL) {
		if (isAreaBeginning(lines[i]))
		{
			map->areaStartIndex = i;
			break;
		}
		char **lineComponents = ft_split(lines[i], ' ');
		if (lineComponents == NULL)
			return (perror("identifyMap():ft_split()"), status);
		newStatus = identifyLine(map, lineComponents, i, status);
		free_stab(lineComponents);
		if (newStatus == NOT_FOUND)
			return status;
		status |= newStatus;
		i++;
	}
	if (status != COMPLETE_STATUS || map->areaStartIndex == NOT_FOUND)
		printf("%sThe given file is incomplete\n", ERROR_MSG);
	return status;
}

int	initIdentifiedMap(t_identifiedMap *map, char *mapFileName)
{
	int fd = open(mapFileName, O_RDONLY);
	if (fd == -1)
	{
		perror("initMap():open()");
		return EXIT_FAILURE;
	}

	char *dataBlock;
	if (initDataBlock(&dataBlock, fd) == EXIT_FAILURE)
		return EXIT_FAILURE;
	char	**lines = ft_split(dataBlock, '\n');
	free(dataBlock);

	int		status = identifyMap(map, lines);
	free_stab(lines);

	if (status == COMPLETE_STATUS && map->areaStartIndex != NOT_FOUND)
		return EXIT_SUCCESS;
	freeIdentifiedMap(map, status);
	return EXIT_FAILURE;
}
