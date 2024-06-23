/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/23 15:31:28 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

# define INDEX_TO_STATUS(index) (1 << (index))
# define NOT_FOUND -1
# define COMPLETE_STATUS 0b111111
# define ERROR_MSG "Error\n"

typedef enum e_identify_index {
	C_INDEX,
	F_INDEX,
	NORTH_INDEX,
	SOUTH_INDEX,
	WEST_INDEX,
	EAST_INDEX
}	t_identify_index;

typedef struct s_rgb {
	int	rCode;
	int	gCode;
	int	bCode;
}	t_rgb;

typedef struct s_identifiedMap {
	char	*surfaces[6];
	int		areaStartIndex;
}	t_identifiedMap;

typedef struct s_map {
	void		*textureObjs[4];
	int			textureObjsWidth[4];
	int			textureObjsHeight[4];
	t_rgb		codes[2];
	char		**area;
	int			*xSize;
	int			ySize;
}	t_formattedMap;

// identifyLine
int		isAreaBeginning(char *line);
int		identifyLine(t_identifiedMap *map, char *line, int lineIndex, int status);

// identifyMap
void	freeIdentifiedMap(t_identifiedMap *map, int status);
int		initIdentifiedMap(t_identifiedMap *identifiedMap, char *mapFileName);

// formattedParts
int		initTextureObjs(void *mlx, t_formattedMap *formatMap, t_identifiedMap *identMap);
int		initCodes(t_rgb *codes, char **surfaces);

// formattedMap
void	printIdentifiedMap(t_identifiedMap *identifiedMap);
int		initFormattedMap(void *mlx, t_formattedMap *map, char *mapFileName);

#endif