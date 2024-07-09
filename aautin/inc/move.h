/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:35:07 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 19:42:55 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "cub3D.h"

void	ft_move_up(t_objs *objs);
void	ft_move_down(t_objs *objs);
void	ft_move_left(t_objs *objs);
void	ft_move_right(t_objs *objs);
void	ft_rotate(double value, t_objs *objs);

#endif