/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 02:11:50 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

# define	NORTH_INDEX
# define	SOUTH_INDEX
# define	WEST_INDEX
# define	EAST_INDEX

typedef struct s_rgb {
	unsigned char	rCode;
	unsigned char	gCode;
	unsigned char	bCode;
}	t_rgb;

typedef struct s_rawData {
	t_list	*dataElements;
	char	*dataBlock;
	char	**texturesFilename;
}	t_rawData;

typedef struct s_map {
	t_rawData	parsing;
	char		**texturesXpm;
	char		**area;
	t_rgb		floarCode;
	t_rgb		ceilingCode;
	char		**xmp;
	int			xSize;
	int			ySize;
}	t_map;

void	initMap(t_map *map, char *mapFileName);

#endif