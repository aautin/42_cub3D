/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandre <alexandre@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 23:35:25 by alexandre         #+#    #+#             */
/*   Updated: 2024/06/18 03:11:31 by alexandre        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

typedef struct s_window {
	void *obj;
	int xSize;
	int ySize;
}	t_window;

int	initWindow(t_window *window, void *mlx, int xSize, int ySize);

#endif