/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:42:11 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 22:47:23 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

typedef struct s_player {
	double	xPosition;
	double	yPosition;
	float	xDirection;
	float	yDirection;
}	t_player;

void	initPlayer(t_player *player, t_formattedMap *map);

#endif