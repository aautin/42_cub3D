/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedParts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/11 14:38:12 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "map.h"
#include "mlx.h"

int	*initAreaxSize(char **area)
{
	int	i = 0;
	while (area[i] != NULL)
		i++;

	int	*xSize = malloc(i * sizeof(int));
	if (xSize == NULL)
	{
		perror("initAreaxSize():malloc()");
		return NULL;
	}

	i = 0;
	while (area[i] != NULL)
	{
		xSize[i] = ft_strlen(area[i]);
		i++;
	}
	return xSize;
}

static int	arePathsAccessible(char **texturesPaths)
{
	t_index	i = NO_INDEX;

	while (i <= EA_INDEX)
	{
		if (access(texturesPaths[i], F_OK) == -1)
		{
			printf("%sCan't open or read %s\n", ERROR_MSG, texturesPaths[i]);
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

int	initTextureObjs(void *mlx, t_map *map, t_identifiedMap *identMap)
{
	int i;

	if (!arePathsAccessible(identMap->surfaces))
		return FAILURE;
	i = NO_INDEX;
	while (i <= EA_INDEX)
	{
		map->textures[i] = malloc(sizeof(t_data));
		if (map->textures[i] == NULL)
		{
			free_textures(mlx, map->textures, NO_INDEX, i - 1);
			return perror("initTextureObjs():malloc()"), FAILURE;
		}
		map->textures[i]->obj = mlx_xpm_file_to_image(mlx, identMap->surfaces[i],
			&map->textures[i]->width, &map->textures[i]->height);
		if (map->textures[i]->obj == NULL)
		{
			free(map->textures[i]);
			free_textures(mlx, map->textures, NO_INDEX, i - 1);
			return perror("initTextureObjs():mlx_xpm_file_to_image()"), FAILURE;
		}
		map->textures[i]->addr = (int *) mlx_get_data_addr(map->textures[i]->obj,
			&map->textures[i]->bits_pixel, &map->textures[i]->line_length,
			&map->textures[i]->endian);
		i++;
	}
	return SUCCESS;
}

static int	initCode(int codes[], char **surfaces, int index)
{
	char	**components = ft_split(surfaces[index], ',');
	if (components == NULL)
	{
		perror("initCode():ft_split()");
		return FAILURE;
	}
	if (!components[0] || !components[1]
		|| !components[2] || components[3])
	{
		printf(ERROR_MSG "The %s rgb-code has an incorrect format\n",
				surfaces[index]);
		return free_double_tab((void **) components, -1), FAILURE;
	}
	if (ft_atoi(components[0]) != (unsigned char) ft_atoi(components[0])
		|| ft_atoi(components[1]) != (unsigned char) ft_atoi(components[1])
		|| ft_atoi(components[2]) != (unsigned char) ft_atoi(components[2]))
	{
		printf(ERROR_MSG "The %s rgb-code has incorrect values\n",
				surfaces[index]);
		return free_double_tab((void **) components, -1), FAILURE;
	}
	codes[index] = ((ft_atoi(components[0]) & 0x0ff) << 16)
		| ((ft_atoi(components[1]) & 0x0ff) << 8)
		| ((ft_atoi(components[2]) & 0x0ff) << 0);
	return free_double_tab((void **) components, -1), SUCCESS;
}

int	initCodes(int codes[], char **surfaces)
{
	t_index	i = C_INDEX;

	while (i <= F_INDEX)
	{
		if (initCode(codes, surfaces + SHIFT, i - SHIFT) == FAILURE)
			return FAILURE;
		i++;
	}
	return SUCCESS;
}
