/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedParts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/06 20:56:03 by aautin           ###   ########.fr       */
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

int	initTextureObjs(void *mlx, t_formattedMap *formatMap, t_identifiedMap *identMap)
{
	void	*newImage;
	t_index i;
	int	newIndex;

	if (!arePathsAccessible(identMap->surfaces))
		return FAILURE;
	i = NO_INDEX;
	newIndex = 0;
	while (i <= EA_INDEX)
	{
		newImage = mlx_xpm_file_to_image(mlx, identMap->surfaces[i],
			&formatMap->textureObjsWidth[newIndex], &formatMap->textureObjsHeight[newIndex]);
		if (newImage == NULL)
		{
			while (--newIndex >= 0)
				mlx_destroy_image(mlx, formatMap->textureObjs[newIndex]);
			printf("%sAn error occured when turning %s to image\n",
				ERROR_MSG, identMap->surfaces[i]);
			return FAILURE;
		}
		formatMap->textureObjs[newIndex] = newImage;
		i++;
		newIndex++;
	}
	return SUCCESS;
}

static int	initCode(t_rgb *codes, char **surfaces, int index)
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
	codes[index - C_INDEX].rCode = ft_atoi(components[0]);
	codes[index - C_INDEX].gCode = ft_atoi(components[1]);
	codes[index - C_INDEX].bCode = ft_atoi(components[2]);
	if (codes[index - C_INDEX].rCode != (unsigned char) codes[index - C_INDEX].rCode
		|| codes[index - C_INDEX].gCode != (unsigned char) codes[index - C_INDEX].gCode
		|| codes[index - C_INDEX].bCode != (unsigned char) codes[index - C_INDEX].bCode)
	{
		printf(ERROR_MSG "The %s rgb-code has incorrect values\n",
				surfaces[index]);
		return free_double_tab((void **) components, -1), FAILURE;
	}
	return free_double_tab((void **) components, -1), EXIT_SUCCESS;
}

int	initCodes(t_rgb *codes, char **surfaces)
{
	t_index	i = C_INDEX;

	while (i <= F_INDEX)
	{
		if (initCode(codes, surfaces, i) == FAILURE)
			return FAILURE;
		i++;
	}
	return SUCCESS;
}
