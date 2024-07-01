/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:35:25 by alexandre         #+#    #+#             */
/*   Updated: 2024/07/01 23:37:55 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

typedef struct s_window {
	void *obj;
	int xSize;
	int ySize;
}	t_window;

void	initWindowHooks(void *mlx, t_window *window, t_formattedMap *map,
			t_player *player);
int		initWindow(void *mlx, t_window *window);

#endif