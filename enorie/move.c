/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:15:22 by root              #+#    #+#             */
/*   Updated: 2024/07/08 14:02:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_move_up(t_all *all)
{
	double	newposx;
	double	newposy;

	newposx = all->pos->x + all->pos->dirx * 0.05;
	newposy = all->pos->y + all->pos->diry * 0.05;
	if (all->map->map[(int)all->pos->y][(int)newposx] != '1')
		all->pos->x = newposx;
	if (all->map->map[(int)newposy][(int)all->pos->x] != '1')
    	all->pos->y = newposy;
	ft_cubed(all);
}

void	ft_move_down(t_all *all)
{
	double	newposx;
	double	newposy;

	newposx = all->pos->x - all->pos->dirx * 0.05;
	newposy = all->pos->y - all->pos->diry * 0.05;
	if (all->map->map[(int)all->pos->y][(int)newposx] != '1')
		all->pos->x = newposx;
	if (all->map->map[(int)newposy][(int)all->pos->x] != '1')
   		all->pos->y = newposy;
	ft_cubed(all);
}

void	ft_move_right(t_all *all)
{
	double	newposx;
	double	newposy;

	newposx = all->pos->x - all->pos->diry * 0.05;
	newposy = all->pos->y + all->pos->dirx * 0.05;
	if (all->map->map[(int)all->pos->y][(int)newposx] != '1')
		all->pos->x = newposx;
	if (all->map->map[(int)newposy][(int)all->pos->x] != '1')
    	all->pos->y = newposy;
	ft_cubed(all);
}

void	ft_move_left(t_all *all)
{
	double	newposx;
	double	newposy;

	newposx = all->pos->x + all->pos->diry * 0.05;
	newposy = all->pos->y - all->pos->dirx * 0.05;
	if (all->map->map[(int)newposy][(int)newposx] != '1')
		if (all->map->map[(int)all->pos->y][(int)newposx] != '1')
		all->pos->x = newposx;
	if (all->map->map[(int)newposy][(int)all->pos->x] != '1')
    	all->pos->y = newposy;
	ft_cubed(all);
}
