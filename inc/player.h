/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:42:11 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/17 01:02:53 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# define NORTH					'N'
# define SOUTH					'S'
# define WEST					'W'
# define EAST					'E'

typedef struct s_player {
	int xPosition;
	int yPosition;
	float xDirection;
	float yDirection;
	float xCasePosition;
	float yCasePosition;
}	t_player;

void	initPlayer(t_player *player, t_map *map);

#endif