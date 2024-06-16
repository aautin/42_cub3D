/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:37:02 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/16 23:38:33 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map {
	char	**content;
	int		xSize;
	int		ySize;
}	t_map;

void	initMap(t_map *map, char *mapFileName);

#endif