/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 11:36:07 by alexandre        ###   ########.fr       */
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

	int	dataBlockSize = 1;
	for (t_list *ptr = dataElements; ptr != NULL; ptr = ptr->next)
		dataBlockSize += ft_strlen(ptr->content);
	*dataBlock = ft_calloc(dataBlockSize, sizeof(char));
	if (*dataBlock == NULL)
	{
		ft_lstclear(&dataElements, &free);
		return EXIT_FAILURE;
	}
	for (t_list *ptr = dataElements; ptr != NULL; ptr = ptr->next)
		ft_strlcat(*dataBlock, ptr->content, dataBlockSize);
	ft_lstclear(&dataElements, &free);
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
