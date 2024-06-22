/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/22 20:49:06 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

# define INDEX_TO_STATUS(index) (1 << (index))
# define NOT_FOUND -1
# define COMPLETE_STATUS 0b00111111
# define ERROR_MSG "Error\n"

typedef enum e_identify_index {
	NORTH_INDEX,
	SOUTH_INDEX,
	WEST_INDEX,
	EAST_INDEX,
	C_INDEX,
	F_INDEX
}	t_identify_index;

typedef struct s_rgb {
	unsigned char	rCode;
	unsigned char	gCode;
	unsigned char	bCode;
}	t_rgb;

typedef struct s_identifiedMap {
	char	*surfaces[6];
	int		areaStartIndex;
}	t_identifiedMap;

typedef struct s_map {
	void		*texturesObj[4];
	char		**area;
	t_rgb		floarCode;
	t_rgb		ceilingCode;
	char		**xmp;
	int			xSize;
	int			ySize;
}	t_formattedMap;

// identifyLine.c
int		isAreaBeginning(char *line);
int		identifyLine(t_identifiedMap *map, char *line, int lineIndex, int status);

// identifyMap.c
void	freeIdentifiedMap(t_identifiedMap *map, int status);
int		initIdentifiedMap(t_identifiedMap *identifiedMap, char *mapFileName);

void	printIdentifiedMap(t_identifiedMap *identifiedMap);
int		initFormattedMap(t_formattedMap *map, char *mapFileName);

#endif