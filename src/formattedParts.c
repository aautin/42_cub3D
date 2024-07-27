/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formattedParts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/27 16:40:40 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "map.h"
#include "mlx.h"

int	*init_area_xsize(char **area, int *sizetab)
{
	int	i;
	int	*xsize;

	i = 0;
	while (area[i] != NULL)
		i++;
	xsize = malloc(i * sizeof(int));
	*sizetab = i;
	if (xsize == NULL)
	{
		perror("init_area_xsize():malloc()");
		return (NULL);
	}
	i = 0;
	while (area[i] != NULL)
	{
		xsize[i] = ft_strlen(area[i]);
		i++;
	}
	return (xsize);
}

static int	are_paths_accessible(char **textures_paths)
{
	t_index	i;

	i = NO_INDEX;
	while (i <= EA_INDEX)
	{
		if (access(textures_paths[i], F_OK) == -1)
		{
			printf("%sCan't open or read %s\n", ERROR_MSG, textures_paths[i]);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	init_texture_objs(void *mlx, t_map *map, t_identified_map *ident_map)
{
	int	i;

	if (!are_paths_accessible(ident_map->surfaces))
		return (FAILURE);
	i = NO_INDEX;
	while (i <= EA_INDEX)
	{
		map->textures[i] = malloc(sizeof(t_data));
		if (map->textures[i] == NULL)
			return (free_textures(mlx, map->textures, NO_INDEX, i - 1),
				perror("init_texture_objs():malloc()"), FAILURE);
		map->textures[i]->obj = mlx_xpm_file_to_image(mlx,
				ident_map->surfaces[i], &map->textures[i]->width,
				&map->textures[i]->height);
		if (map->textures[i]->obj == NULL)
			return (free(map->textures[i]), free_textures(mlx,
					map->textures, NO_INDEX, i - 1),
				perror("init_texture_objs():mlx_xpm_file_to_image()"),
				FAILURE);
		map->textures[i]->addr = (int *) mlx_get_data_addr(
				map->textures[i]->obj, &map->textures[i]->bits_pixel,
				&map->textures[i]->line_length, &map->textures[i]->endian);
		i++;
	}
	return (SUCCESS);
}

static int	init_code(int codes[], char **surfaces, int i)
{
	char	**components;

	components = ft_split(surfaces[i], ',');
	if (components == NULL)
		return (perror("initCode():ft_split()"), FAILURE);
	if (!components[0] || !components[1]
		|| !components[2] || components[3])
	{
		printf(ERROR_MSG "The %s rgb-code has an incorrect format\n",
			surfaces[i]);
		return (free_double_tab((void **) components, -1), FAILURE);
	}
	if (ft_atoi(components[0]) != (unsigned char) ft_atoi(components[0])
		|| ft_atoi(components[1]) != (unsigned char) ft_atoi(components[1])
		|| ft_atoi(components[2]) != (unsigned char) ft_atoi(components[2]))
	{
		printf(ERROR_MSG "The %s rgb-code has incorrect values\n", surfaces[i]);
		return (free_double_tab((void **) components, -1), FAILURE);
	}
	codes[i] = ((ft_atoi(components[0]) & 0x0ff) << 16)
		| ((ft_atoi(components[1]) & 0x0ff) << 8)
		| ((ft_atoi(components[2]) & 0x0ff) << 0);
	return (free_double_tab((void **) components, -1), SUCCESS);
}

int	init_codes(int codes[], char **surfaces)
{
	t_index	i;

	i = C_INDEX;
	while (i <= F_INDEX)
	{
		if (init_code(codes, surfaces + SHIFT, i - SHIFT) == FAILURE)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
