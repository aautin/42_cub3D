/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/09 19:33:26 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"

void	free_textures(void *mlx, t_data *textures[])
{
	t_index	i = NO_INDEX;

	while (i <= EA_INDEX)
	{
		mlx_destroy_image(mlx, textures[i]->obj);
		i++;
	}
}

void	cleanArea(char **area, int *xSize)
{
	int	x, y;

	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (x < xSize[y])
		{
			if (ft_strchr(" TNSWE", area[y][x]) != NULL)
				area[y][x] = '0';
			x++;
		}
		y++;
	}
}

void	free_map(void *mlx, t_map *map)
{
	free_double_tab((void **) map->area, -1);
	free_textures(mlx, map->textures);
}

int	initFormattedMap(void *mlx, t_map *map, char *mapFileName, t_player *player)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaIndex = NOT_FOUND;
	if (initIdentification(&identifiedMap, mapFileName, &map->area) == FAILURE)
		return FAILURE;
	if (initCodes(map->codes, identifiedMap.surfaces) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	if (initTextureObjs(mlx, map, &identifiedMap) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	if (initArea(map, player) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		free_textures(mlx, map->textures);
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return FAILURE;
	}
	return freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS), SUCCESS;
}
