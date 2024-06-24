/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedArea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:24:21 by aautin            #+#    #+#             */
/*   Updated: 2024/06/24 17:20:23 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "map.h"

int	floodfile(t_formattedMap *map)
{
	i = 0;
	while (map->area[i] != NULL)
	{
		j = 0;
		while (map->area[i][j] != '\0')
		{
			if (ft_strchr("NSWE0", map->area[i][j]) != NULL)
			{
				if (map->player)
				{
					printf("%sMap has several players\n", ERROR_MSG);
					return EXIT_FAILURE;
				}
				map->player = map->area[i][j];
			}
			else if (map->area[i][j] == '')
			j++;
		}
		i++;
	}
	return 
}

int	checkArea(t_formattedMap *map)
{
	int expansion = TRUE;

	map->player = 0;

	while (expansion != 0)
	{
		expansion = floodfile(map);
		if (expansion == EXIT_FAILURE)
			return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}