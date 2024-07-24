/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/24 03:37:58 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "data.h"
# include "libft.h"
# include "player.h"

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

typedef struct s_identified_map {
	char	*surfaces[6];
	int		area_index;
}	t_identified_map;

typedef struct s_map {
	t_data	*textures[4];
	int		codes[2];
	char	**area;
}	t_map;

// identify_line
int		is_area_beginning(char *line);
int		identify_line(t_identified_map *map, char *line, int line_index,
			int status);

// identifyMap
void	free_identified_map(t_identified_map *map, int status);
int		init_identification(t_identified_map *identified_map,
			char *map_file_name, char ***areaPtr);

// formattedArea
int		init_area(t_map *map, t_player *player);

// formattedParts
int		*init_area_xsize(char **area);
int		init_texture_objs(void *mlx, t_map *format_map,
			t_identified_map *ident_map);
int		init_codes(int codes[], char **surfaces);

// formattedMap
void	free_textures(void *mlx, t_data *textures[], int start, int end);
void	clean_area(char **area, int *xsize);
void	free_map(void *mlx, t_map *map);
int		init_formatted_map(void *mlx, t_map *map, char *map_file_name,
			t_player *player);

#endif