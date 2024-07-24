/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/24 01:22:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "map.h"
#include "mlx.h"

void	free_textures(void *mlx, t_data *textures[], int start, int end)
{
	while (start <= end)
	{
		mlx_destroy_image(mlx, textures[start]->obj);
		free(textures[start]);
		start++;
	}
}

void	clean_area(char **area, int *xsize)
{
	int	x;
	int	y;

	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (x < xsize[y])
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
	free_textures(mlx, map->textures, NO_INDEX, EA_INDEX);
	free(map);
}

int	init_formatted_map(void *mlx, t_map *map, char *map_file_name,
		t_player *player)
{
	t_identified_map	identified_map;

	identified_map.area_index = NOT_FOUND;
	if (init_identification(&identified_map, map_file_name,
			&map->area) == FAILURE)
		return (FAILURE);
	if (init_codes(map->codes, identified_map.surfaces) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		return (free_identified_map(&identified_map, COMPLETE_STATUS), FAILURE);
	}
	if (init_texture_objs(mlx, map, &identified_map) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		free_identified_map(&identified_map, COMPLETE_STATUS);
		return (FAILURE);
	}
	if (init_area(map, player) == FAILURE)
	{
		free_double_tab((void **) map->area, -1);
		free_textures(mlx, map->textures, NO_INDEX, EA_INDEX);
		free_identified_map(&identified_map, COMPLETE_STATUS);
		return (FAILURE);
	}
	return (free_identified_map(&identified_map, COMPLETE_STATUS), SUCCESS);
}
