/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/06 20:46:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

# define INDEX_TO_STATUS(index) (1 << (index))
# define NOT_FOUND -1
# define COMPLETE_STATUS 0b111111
# define ERROR_MSG "Error\n"

typedef enum e_index {
	NO_INDEX,
	SO_INDEX,
	WE_INDEX,
	EA_INDEX,
	C_INDEX,
	F_INDEX
}	t_index;

typedef struct s_rgb {
	int	rCode;
	int	gCode;
	int	bCode;
}	t_rgb;

typedef struct s_identifiedMap {
	char	*surfaces[6];
	int		areaIndex;
}	t_identifiedMap;

typedef struct s_formattedMap {
	void	*textureObjs[4];
	int		textureObjsWidth[4];
	int		textureObjsHeight[4];
	t_rgb	codes[2];
	char	**area;
	int		*xSize;
	char	player;
}	t_formattedMap;

// identifyLine
int		isAreaBeginning(char *line);
int		identifyLine(t_identifiedMap *map, char *line, int lineIndex,
			int status);

// identifyMap
void	freeIdentifiedMap(t_identifiedMap *map, int status);
int		initIdentification(t_identifiedMap *identifiedMap, char *mapFileName,
			char ***areaPtr);

// formattedArea
int		initArea(t_formattedMap *map);

// formattedParts
int		*initAreaxSize(char **area);
int		initTextureObjs(void *mlx, t_formattedMap *formatMap,
			t_identifiedMap *identMap);
int		initCodes(t_rgb *codes, char **surfaces);

// formattedMap
void	cleanArea(char **area, int *xSize);
void	freeFormattedMap(void *mlx, t_formattedMap *map);
int		initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName);

#endif