/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 02:07:05 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "map.h"

void	initMap(t_map *map, char *mapFileName)
{
	int fd = open(mapFileName, O_RDONLY);

	t_list *mapRows;
	mapRows = NULL;

	char *row = get_next_line(fd);
	map->ySize = 0;
	while (row)
	{
		ft_lstadd_front(&mapRows, ft_lstnew(row));
		map->ySize++;
		row = get_next_line(fd);
	}
	map->xSize = ft_strlen(mapRows->content) - 1;
	map->area = malloc(map->ySize * sizeof(char *));

	int rowIndex = 0;
	while (rowIndex < map->ySize)
	{
		map->area[rowIndex] = mapRows->content;
		map->area[rowIndex][map->xSize - 1] = '\0';
		mapRows = mapRows->next;
		rowIndex++;
	}
}
