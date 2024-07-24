/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedArea.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:24:21 by aautin            #+#    #+#             */
/*   Updated: 2024/07/24 04:37:11 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "map.h"
#include "player.h"

static int	check_player(char **area)
{
	char	player;
	int		x;
	int		y;

	player = 0;
	y = 0;
	while (area[y] != NULL)
	{
		x = 0;
		while (area[y][x] != '\0')
		{
			if (ft_strchr("NSWE", area[y][x]) != NULL && player)
				return (printf(ERROR_MSG "Map has several players\n"), FAILURE);
			else if (ft_strchr("NSWE", area[y][x]))
				player = area[y][x];
			x++;
		}
		y++;
	}
	if (!player)
	{
		printf(ERROR_MSG "Map has no player\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	floodchar(int *xsize, char **area, int line, int col)
{
	int	status;
	int	step;

	status = FAILURE;
	if (line == 0 || col == 0 || xsize[line - 1] - 1 < col || !area[line + 1]
		|| xsize[line + 1] - 1 < col || area[line][col + 1] == '\0')
		return (NOT_FOUND);
	step = -1;
	while (step <= 1)
	{
		if (area[line + step][col] && ft_strchr("0 ", area[line + step][col]))
		{
			status = SUCCESS;
			area[line + step][col] = 'T';
		}
		if (area[line][col + step] && ft_strchr("0 ", area[line][col + step]))
		{
			status = SUCCESS;
			area[line][col + step] = 'T';
		}
		step += 2;
	}
	return (status);
}

static int	floodline(t_map *map, int line_i, int *expansion, int *xsize)
{
	int	col_i;
	int	flood_status;

	col_i = 0;
	while (map->area[line_i][col_i] != '\0')
	{
		if (ft_strchr("NSWET", map->area[line_i][col_i]) != NULL)
		{
			flood_status = floodchar(xsize, map->area, line_i, col_i);
			if (flood_status == NOT_FOUND)
			{
				printf(ERROR_MSG "Map isn't closed\n");
				return (FAILURE);
			}
			else if (flood_status == SUCCESS)
				*expansion = TRUE;
		}
		else if (ft_strchr("10 ", map->area[line_i][col_i]) == NULL)
		{
			printf(ERROR_MSG "Map has wrong chars\n");
			return (FAILURE);
		}
		col_i++;
	}
	return (SUCCESS);
}

static int	floodfill(t_map *map, int *xsize)
{
	int	expansion;
	int	i;

	expansion = TRUE;
	while (expansion == TRUE)
	{
		expansion = FALSE;
		i = 0;
		while (map->area[i] != NULL)
		{
			if (floodline(map, i, &expansion, xsize) == FAILURE)
				return (FAILURE);
			i++;
		}
	}
	return (SUCCESS);
}

int	init_area(t_map *map, t_player *player)
{
	int	*xsize;

	xsize = init_area_xsize(map->area);
	if (xsize == NULL)
		return (FAILURE);
	if (floodfill(map, xsize) == SUCCESS && check_player(map->area) == SUCCESS)
	{
		init_player(player, map->area);
		clean_area(map->area, xsize);
		free(xsize);
		return (SUCCESS);
	}
	free(xsize);
	return (FAILURE);
}
