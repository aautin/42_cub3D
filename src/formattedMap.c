/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedMap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/23 15:25:52 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "mlx.h"
#include "map.h"

void	printIdentifiedMap(t_identifiedMap *identifiedMap)
{
	printf("C_CODE: %s\n", identifiedMap->surfaces[C_INDEX]);
	printf("F_CODE: %s\n", identifiedMap->surfaces[F_INDEX]);
	printf("NO path-texture: %s\n", identifiedMap->surfaces[NORTH_INDEX]);
	printf("SO path-texture: %s\n", identifiedMap->surfaces[SOUTH_INDEX]);
	printf("WE path-texture: %s\n", identifiedMap->surfaces[WEST_INDEX]);
	printf("EA path-texture: %s\n", identifiedMap->surfaces[EAST_INDEX]);
	printf("index of the first line of the map:%d\n", identifiedMap->areaStartIndex);
}

static int	arePathsAccessible(char **paths)
{
	int	i = NORTH_INDEX;

	while (i <= EAST_INDEX)
	{
		if (access(paths[i], F_OK) == -1)
		{
			printf("%sCan't open or read %s\n", ERROR_MSG, paths[i]);
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

int	initTextureObjs(void *mlx, t_formattedMap *formatMap, t_identifiedMap *identMap)
{
	void	*newImage;
	int 	i;

	if (!arePathsAccessible(identMap->surfaces))
		return EXIT_FAILURE;
	i = 0;
	while (i <= EAST_INDEX)
	{
		newImage = mlx_xpm_file_to_image(mlx, identMap->surfaces[i],
			&formatMap->textureObjsWidth[i], &formatMap->textureObjsHeight[i]);
		if (newImage == NULL)
		{
			while (i-- > 0)
				mlx_destroy_image(mlx, formatMap->textureObjs[i]);
			printf("%sAn error occured when turning %s to image\n",
				ERROR_MSG, identMap->surfaces[i]);
			return EXIT_FAILURE;
		}
		formatMap->textureObjs[i] = newImage;
		i++;
	}
	return EXIT_SUCCESS;
}

int	initCode(t_rgb *codes, char **surfaces, int index)
{
	char	**components = ft_split(surfaces[index], ',');
	if (components == NULL)
	{
		perror("initCode():ft_split()");
		return EXIT_FAILURE;
	}
	if (!components[0] || !components[1]
		|| !components[2] || components[3])
	{
		printf("%sThe %s rgb-code has an incorrect format\n",
			ERROR_MSG, surfaces[index]);
		return free_double_tab((void **) components, -1), EXIT_FAILURE;
	}
	codes[index].rCode = ft_atoi(components[0]);
	codes[index].gCode = ft_atoi(components[1]);
	codes[index].bCode = ft_atoi(components[2]);
	if (codes[index].rCode != (unsigned char) codes[index].rCode
		|| codes[index].gCode != (unsigned char) codes[index].gCode
		|| codes[index].bCode != (unsigned char) codes[index].bCode)
	{
		printf("%sThe %s rgb-code has incorrect values\n",
			ERROR_MSG, surfaces[index]);
		return free_double_tab((void **) components, -1), EXIT_FAILURE;
	}
	return free_double_tab((void **) components, -1), EXIT_SUCCESS;
}

int	initCodes(t_rgb *codes, char **surfaces)
{
	int	i = 0;

	while (i <= F_INDEX)
	{
		if (initCode(codes, surfaces, i) == EXIT_FAILURE)
			return EXIT_FAILURE;
		i++;
	}
	return EXIT_SUCCESS;
}

void	freeTextureObjs(void *mlx, void **textureObjs)
{
	int	i = 0;

	while (i <= EAST_INDEX)
	{
		mlx_destroy_image(mlx, textureObjs[i]);
		i++;
	}
}

int	initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName)
{
	t_identifiedMap identifiedMap;

	identifiedMap.areaStartIndex = NOT_FOUND;
	if (initIdentifiedMap(&identifiedMap, mapFileName) == EXIT_FAILURE)
		return EXIT_FAILURE;
	printIdentifiedMap(&identifiedMap);
	if (initCodes(map->codes, identifiedMap.surfaces) == EXIT_FAILURE)
	{
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	if (initTextureObjs(mlx, map, &identifiedMap) == EXIT_FAILURE)
	{
		freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
		return EXIT_FAILURE;
	}
	// .. here have to parse map area
	freeIdentifiedMap(&identifiedMap, COMPLETE_STATUS);
	return EXIT_SUCCESS;
}
