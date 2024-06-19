/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/19 22:37:20 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

#include "ft_printf.h"

void	freeIdentifiedMap(t_identifiedMap *map, int status)
{
	if (status & NO_TEXTURE)
		free(map->texturesFilename[NORTH_INDEX]);
	if (status & SO_TEXTURE)
		free(map->texturesFilename[SOUTH_INDEX]);
	if (status & WE_TEXTURE)
		free(map->texturesFilename[WEST_INDEX]);
	if (status & EA_TEXTURE)
		free(map->texturesFilename[EAST_INDEX]);
	if (status & F_CODE)
		free(map->code[F_INDEX]);
	if (status & C_CODE)
		free(map->code[C_INDEX]);
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


static int	identifyMap(t_identifiedMap *map, char **lines)
{
	int	status = 0;
	int	i = 0;
	while (lines[i] != NULL) {
		int	j = 0;
		int	newStatus = 0;
		while (lines[i][j] == ' ')
			i++;
		if (seemToBeCode(&lines[i][j]))
			newStatus = identifyCode(map, &lines[i][j + 1], lines[i][j]);
		else if (seemToBeTexture(&lines[i][j]))
			newStatus = identifyTexture(map, &lines[i][j]);
		else if (seemToBeArea(lines[i][j]))
		{
			map->mapStartIndex = i;
			break;
		}
		if (newStatus == 0)
		{
			printf("%s\nLine %d incorrect\n", ERROR_MSG, i);
			break;
		}
		status |= newStatus;
		i++;
	}
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
	int		status = identifyMap(map, lines);
	free(dataBlock);
	free_stab(lines);
	if (status & COMPLETE && map->mapStartIndex != NOT_FOUND)
		return EXIT_SUCCESS;
	freeIdentifiedMap(map, status);
	return EXIT_FAILURE;
}
