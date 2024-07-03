/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:35:25 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/03 19:47:31 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "map.h"
# include "player.h"

# define WINDOW_MIN_SIZE 480

typedef struct s_window {
	void *obj;
	int xSize;
	int ySize;
}	t_window;

typedef struct s_handlerParam {
	void 			*mlx;
	t_formattedMap	*map;
	t_player		*player;
	t_window		*window;
}	t_handlerParam;

void	initWindowHooks(t_handlerParam *param);
int		initWindow(void *mlx, t_window *window);

#endif