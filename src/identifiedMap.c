/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 20:21:41 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "map.h"

void	freeIdentifiedMap(t_identifiedMap *map, int status)
{
	t_identify_index	i = C_INDEX;

	while (i <= EAST_INDEX)
	{
		if (status & INDEX_TO_STATUS(i))
			free(map->surfaces[i]);
		i++;
	}
}

static void	eraseNewlines(char **lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i] != NULL)
	{
		j = 0;
		while (lines[i][j] != '\0')
		{
			if (lines[i][j] == '\n')
			{
				lines[i][j] = '\0';
				break ;
			}
			j++;
		}
		i++;
	}
}

static int	identifyMap(t_identifiedMap *map, char **lines)
{
	int	newStatus;
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (lines[i] != NULL)
	{
		if (isAreaBeginning(lines[i]))
		{
			map->areaIndex = i;
			break;
		}
		newStatus = identifyLine(map, lines[i], i, status);
		if (newStatus == NOT_FOUND)
			return status;
		status |= newStatus;
		i++;
	}
	if (status != COMPLETE_STATUS || map->areaIndex == NOT_FOUND)
		printf(ERROR_MSG "The file given is incomplete or in disorder\n");
	return status;
}

static int	identifyArea(char **mapContent, int areaIndex, char ***areaPtr)
{
	char	**newPtr;
	int		areaSize = 0;

	while (mapContent[areaIndex + areaSize] != NULL)
		areaSize++;
	newPtr = malloc((areaSize + 1) * sizeof(char *));
	if (newPtr == NULL)
	{
		perror("identifyArea():malloc()");
		return EXIT_FAILURE;
	}
	areaSize = 0;
	while (mapContent[areaIndex + areaSize] != NULL)
	{
		newPtr[areaSize] = mapContent[areaIndex + areaSize];
		areaSize++;
	}
	newPtr[areaSize] = NULL;
	while (areaIndex-- > 0)
		free(mapContent[areaIndex]);
	free(mapContent);
	*areaPtr = newPtr;
	return EXIT_SUCCESS;
}

int	initIdentification(t_identifiedMap *map, char *mapFileName, char ***area)
{
	int const	fd = open(mapFileName, O_RDONLY);
	if (fd == -1)
	{
		printf(ERROR_MSG "Can't open or read the given file\n");
		return EXIT_FAILURE;
	}

	t_list	*dataElements = NULL;
	dataElements = file_to_lst(fd);
	close(fd);

	char	**mapContent = (char **) lst_to_double_tab(dataElements, NULL);
	eraseNewlines(mapContent);

	int		status = identifyMap(map, mapContent);
	ft_lstclear(&dataElements, NULL);

	if (status == COMPLETE_STATUS && map->areaIndex != NOT_FOUND
		&& identifyArea(mapContent, map->areaIndex, area) == EXIT_SUCCESS)
		return EXIT_SUCCESS;

	free_double_tab((void **) mapContent, -1);
	freeIdentifiedMap(map, status);
	return EXIT_FAILURE;
}
