/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiedMap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 19:08:29 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

#include "ft_printf.h"

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
		if ((lines[i][j] == 'F' || lines[i][j] == 'C') 
			&& lines[i][j + 1] == ' ')
			newStatus = identifyCode(map, &lines[i][j + 1]);
		else if (ft_strnstr(&lines[i][j], "NO ", 3)
			|| ft_strnstr(&lines[i][j], "SO ", 3)
			|| ft_strnstr(&lines[i][j], "WE ", 3)
			|| ft_strnstr(&lines[i][j], "EA ", 3))
			newStatus = identifyTexture(map, &lines[i][j]);
		else if (ft_strchr("10", lines[i][j]))
			newStatus = identifyArea(map, &lines[i]);
		if (newStatus == 0)
			break;
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
	return EXIT_SUCCESS;
}
