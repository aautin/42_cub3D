/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:42:11 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 23:39:04 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "map.h"

typedef struct s_player {
	int		isMoving;
	int		isRotating;
	double	xPosition;
	double	yPosition;
	float	xDirection;
	float	yDirection;
}	t_player;

int		makePlayerMove(char **area, t_player *player, int keycode);
void	initPlayer(t_player *player, t_formattedMap *map);

#endif