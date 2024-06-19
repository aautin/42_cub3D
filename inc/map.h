/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/19 22:42:05 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "libft.h"

# define NOT_FOUND -1 
# define ERROR_MSG "Error\n"

typedef enum e_identify_index {
	NORTH_INDEX,
	SOUTH_INDEX,
	WEST_INDEX,
	EAST_INDEX,
	C_INDEX = 0,
	F_INDEX = 1
}	t_identify_index;

typedef enum e_identify_status {
	C_CODE = (1 << 0),
	F_CODE = (1 << 1),
	NO_TEXTURE = (1 << 2),
	SO_TEXTURE = (1 << 3),
	WE_TEXTURE = (1 << 4),
	EA_TEXTURE = (1 << 5),
	COMPLETE = (C_CODE | F_CODE
			| NO_TEXTURE | SO_TEXTURE | WE_TEXTURE | EA_TEXTURE)
}	t_identify_status;

typedef struct s_rgb {
	unsigned char	rCode;
	unsigned char	gCode;
	unsigned char	bCode;
}	t_rgb;

typedef struct s_identifiedMap {
	char	*texturesFilename[4];
	char	*code[2];
	int		mapStartIndex;
}	t_identifiedMap;

typedef struct s_map {
	char		*texturesXpm[4];
	char		**area;
	t_rgb		floarCode;
	t_rgb		ceilingCode;
	char		**xmp;
	int			xSize;
	int			ySize;
}	t_formattedMap;

int		seemToBeCode(char *line);
int		seemToBeTexture(char *line);
int		seemToBeArea(char letter);
int		identifyCode(t_identifiedMap *map, char *line, int letter);
int		identifyTexture(t_identifiedMap *map, char *line);

void	freeIdentifiedMap(t_identifiedMap *map, int status);
int		initIdentifiedMap(t_identifiedMap *identifiedMap, char *mapFileName);

int		initMap(t_formattedMap *map, char *mapFileName);

#endif