/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:05:28 by root              #+#    #+#             */
/*   Updated: 2024/07/24 03:38:12 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "map.h"

int	index_to_status(int index)
{
	return (1 << index);
}

t_data	*ft_find_texture(int side, double raydirx, double raydiry, t_map *map)
{
	if (side == 0 && raydirx > 0)
		return (map->textures[SO_INDEX]);
	else if (side == 0 && raydirx < 0)
		return (map->textures[NO_INDEX]);
	else if (side == 1 && raydiry > 0)
		return (map->textures[EA_INDEX]);
	else
		return (map->textures[WE_INDEX]);
}
