/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedParts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/23 15:30:46 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "mlx.h"
#include "map.h"

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

static int	initCode(t_rgb *codes, char **surfaces, int index)
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
