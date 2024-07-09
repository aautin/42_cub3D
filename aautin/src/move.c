/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:15:22 by root              #+#    #+#             */
/*   Updated: 2024/07/08 19:49:01 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "cub3D.h"

void	ft_move_up(t_objs *objs)
{
	double	newposx;
	double	newposy;

	newposx = objs->player->x + objs->player->dirx * 0.05;
	newposy = objs->player->y + objs->player->diry * 0.05;
	if (objs->map->area[(int)objs->player->y][(int)newposx] != '1')
		objs->player->x = newposx;
	if (objs->map->area[(int)newposy][(int)objs->player->x] != '1')
    	objs->player->y = newposy;
	ft_cub3d(objs);
}

void	ft_move_down(t_objs *objs)
{
	double	newposx;
	double	newposy;

	newposx = objs->player->x - objs->player->dirx * 0.05;
	newposy = objs->player->y - objs->player->diry * 0.05;
	if (objs->map->area[(int)objs->player->y][(int)newposx] != '1')
		objs->player->x = newposx;
	if (objs->map->area[(int)newposy][(int)objs->player->x] != '1')
   		objs->player->y = newposy;
	ft_cub3d(objs);
}

void	ft_move_right(t_objs *objs)
{
	double	newposx;
	double	newposy;

	newposx = objs->player->x - objs->player->diry * 0.05;
	newposy = objs->player->y + objs->player->dirx * 0.05;
	if (objs->map->area[(int)objs->player->y][(int)newposx] != '1')
		objs->player->x = newposx;
	if (objs->map->area[(int)newposy][(int)objs->player->x] != '1')
    	objs->player->y = newposy;
	ft_cub3d(objs);
}

void	ft_move_left(t_objs *objs)
{
	double	newposx;
	double	newposy;

	newposx = objs->player->x + objs->player->diry * 0.05;
	newposy = objs->player->y - objs->player->dirx * 0.05;
	if (objs->map->area[(int)objs->player->y][(int)newposx] != '1')
		objs->player->x = newposx;
	if (objs->map->area[(int)newposy][(int)objs->player->x] != '1')
    	objs->player->y = newposy;
	ft_cub3d(objs);
}

void	ft_rotate(double value, t_objs *objs)
{
	t_player	*player;
	double		oldplanex;
	double		olddirx;

	player = objs->player;
	olddirx = objs->player->dirx;
	player->dirx = player->dirx * cos(value) - player->diry * sin(value);
	player->diry = olddirx * sin(value) + player->diry * cos(value);
	oldplanex = player->planex;
	player->planex = player->planex * cos(value) - player->planey * sin(value);
	player->planey = oldplanex * sin(value) + player->planey * cos(value);
	ft_cub3d(objs);
}
