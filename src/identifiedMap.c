/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 14:46:52 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

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

int	initIdentifiedMap(t_identifiedMap *identifiedMap, char *mapFileName)
{
	(void) identifiedMap;

	int fd = open(mapFileName, O_RDONLY);
	if (fd == -1)
	{
		perror("initMap():open()");
		return EXIT_FAILURE;
	}

	char *dataBlock;
	if (initDataBlock(&dataBlock, fd) == EXIT_FAILURE)
		return EXIT_FAILURE;
	free(dataBlock);	
	return EXIT_SUCCESS;
}
