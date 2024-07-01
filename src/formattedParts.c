/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedParts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/02 20:44:32 by aautin           ###   ########.fr       */
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
	t_format_index	i = NO_FORMAT_INDEX;

	while (i <= EA_FORMAT_INDEX)
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
	void			*newImage;
	t_format_index 	i;

	if (!arePathsAccessible(identMap->surfaces + 2))
		return FAILURE;
	i = NO_FORMAT_INDEX;
	while (i <= EA_FORMAT_INDEX)
	{
		newImage = mlx_xpm_file_to_image(mlx, identMap->surfaces[i + NO_IDENTIFY_INDEX],
			&formatMap->textureObjsWidth[i], &formatMap->textureObjsHeight[i]);
		if (newImage == NULL)
		{
			while (--i >= 0)
				mlx_destroy_image(mlx, formatMap->textureObjs[i]);
			printf("%sAn error occured when turning %s to image\n",
				ERROR_MSG, identMap->surfaces[i + NO_IDENTIFY_INDEX]);
			return FAILURE;
		}
		formatMap->textureObjs[i] = newImage;
		i++;
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
	codes[index].rCode = ft_atoi(components[0]);
	codes[index].gCode = ft_atoi(components[1]);
	codes[index].bCode = ft_atoi(components[2]);
	if (codes[index].rCode != (unsigned char) codes[index].rCode
		|| codes[index].gCode != (unsigned char) codes[index].gCode
		|| codes[index].bCode != (unsigned char) codes[index].bCode)
	{
		printf(ERROR_MSG "The %s rgb-code has incorrect values\n",
				surfaces[index]);
		return free_double_tab((void **) components, -1), FAILURE;
	}
	return free_double_tab((void **) components, -1), EXIT_SUCCESS;
}

int	initCodes(t_rgb *codes, char **surfaces)
{
	t_identify_index	i = C_IDENTIFY_INDEX;

	while (i <= F_IDENTIFY_INDEX)
	{
		if (initCode(codes, surfaces, i) == FAILURE)
			return FAILURE;
		i++;
	}
	return SUCCESS;
}
