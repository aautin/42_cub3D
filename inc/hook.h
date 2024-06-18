/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 00:57:01 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 02:12:37 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOK_H
# define HOOK_H

# include "map.h"
# include "player.h"
# include "window.h"

# define DESTROY_WINDOW_EVENT   17
# define DESTROY_WINDOW_MASK    0
# define KEY_PRESSED_EVENT		2
# define KEY_PRESSED_MASK		(1L<<0)

typedef struct s_keyHandlerParam {
	t_window	*window;
	t_map		*map;
	t_player	*player;
	void		*mlx;
}	t_keyHandlerParam;

void    setWindowHooks(t_keyHandlerParam *param);

#endif