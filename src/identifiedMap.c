/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/24 00:54:56 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"
#include "map.h"

void	freeIdentifiedMap(t_identifiedMap *map, int status)
{
	t_index	i = NO_INDEX;

	while (i <= F_INDEX)
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
		return FAILURE;
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
	return SUCCESS;
}

int	initIdentification(t_identifiedMap *map, char *mapFileName, char ***area)
{
	t_list		*dataElements;
	int const	fd = open_fd(mapFileName);

	if (fd == -1)
		return FAILURE;
	dataElements = fd_to_lst(fd);
	if (dataElements == NULL)
		return FAILURE;
	char	**mapContent = (char **) lst_to_double_tab(dataElements, NULL);
	ft_lstclear(&dataElements, NULL);
	if (mapContent == NULL)
		return FAILURE;
	eraseNewlines(mapContent);

	int		status = identifyMap(map, mapContent);

	if (status == COMPLETE_STATUS && map->areaIndex != NOT_FOUND
		&& identifyArea(mapContent, map->areaIndex, area) == SUCCESS)
		return SUCCESS;

	free_double_tab((void **) mapContent, -1);
	freeIdentifiedMap(map, status);
	return FAILURE;
}
