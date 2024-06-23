/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/23 14:31:19 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

void	freeIdentifiedMap(t_identifiedMap *map, int status)
{
	int	i = C_INDEX;

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
			map->areaStartIndex = i;
			break;
		}
		newStatus = identifyLine(map, lines[i], i, status);
		if (newStatus == NOT_FOUND)
			return status;
		status |= newStatus;
		i++;
	}
	if (status != COMPLETE_STATUS || map->areaStartIndex == NOT_FOUND)
		printf("%sThe file given is incomplete or in disorder\n", ERROR_MSG);
	return status;
}

int	initIdentifiedMap(t_identifiedMap *map, char *mapFileName)
{
	int fd = open(mapFileName, O_RDONLY);
	if (fd == -1)
	{
		printf("%sCan't open or read the given file\n", ERROR_MSG);
		return EXIT_FAILURE;
	}

	t_list	*dataElements = NULL;
	dataElements = file_to_lst(fd);

	char	**mapContent = (char **) lst_to_double_tab(dataElements, NULL);
	eraseNewlines(mapContent);

	int		status = identifyMap(map, mapContent);
	ft_lstclear(&dataElements, NULL);
	free_double_tab((void **) mapContent, -1);

	if (status == COMPLETE_STATUS && map->areaStartIndex != NOT_FOUND)
		return EXIT_SUCCESS;

	freeIdentifiedMap(map, status);
	return EXIT_FAILURE;
}
