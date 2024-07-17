/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/11 14:31:42 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "data.h"
# include "libft.h"
# include "player.h"

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
	F_INDEX,
	SHIFT = C_INDEX
}	t_index;

typedef struct s_identifiedMap {
	char	*surfaces[6];
	int		areaIndex;
}	t_identifiedMap;

typedef struct s_map {
	t_data	*textures[4];
	int		codes[2];
	char	**area;
}	t_map;

// identifyLine
int		isAreaBeginning(char *line);
int		identifyLine(t_identifiedMap *map, char *line, int lineIndex,
			int status);

// identifyMap
void	freeIdentifiedMap(t_identifiedMap *map, int status);
int		initIdentification(t_identifiedMap *identifiedMap, char *mapFileName,
			char ***areaPtr);

// formattedArea
int		initArea(t_map *map, t_player *player);

// formattedParts
int		*initAreaxSize(char **area);
int		initTextureObjs(void *mlx, t_map *formatMap,
			t_identifiedMap *identMap);
int		initCodes(int codes[], char **surfaces);

// formattedMap
void	free_textures(void *mlx, t_data *textures[], int start, int end);
void	cleanArea(char **area, int *xSize);
void	free_map(void *mlx, t_map *map);
int		initFormattedMap(void *mlx, t_map *map, char *mapFileName, t_player *player);

#endif