/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:55:01 by root              #+#    #+#             */
/*   Updated: 2024/07/01 13:21:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_rotate(int keycode, t_all *all)
{
	t_pos	*pos;
	double	oldplanex;
	double	olddirx;

	if (keycode == XK_Right)
	{
		pos = all->pos;
		olddirx = all->pos->dirx;
		pos->dirx = pos->dirx * cos(0.05) - pos->diry * sin(0.05);
		pos->diry = olddirx * sin(0.05) + pos->diry * cos(0.05);
		oldplanex = pos->planex;
		pos->planex = pos->planex * cos(0.05) - pos->planey * sin(0.05);
		pos->planey = oldplanex * sin(0.05) + pos->planey * cos(0.05);
	}
	if (keycode == XK_Left)
	{
		pos = all->pos;
		olddirx = all->pos->dirx;
		pos->dirx = pos->dirx * cos(-0.05) - pos->diry * sin(-0.05);
		pos->diry = olddirx * sin(-0.05) + pos->diry * cos(-0.05);
		oldplanex = pos->planex;
		pos->planex = pos->planex * cos(-0.05) - pos->planey * sin(-0.05);
		pos->planey = oldplanex * sin(-0.05) + pos->planey * cos(-0.05);
	}
	ft_cubed(all);
}

int	key_hook(int keycode, t_all *all)
{
	if (keycode == XK_Escape)
	{
		mlx_destroy_window(all->vars->mlx, all->vars->win);
		mlx_loop_end(all->vars->mlx);
	}
	if (keycode == XK_w)
		ft_move_up(all);
	if (keycode == XK_a)
		ft_move_left(all);
	if (keycode == XK_s)
		ft_move_down(all);
	if (keycode == XK_d)
		ft_move_right(all);
	if (keycode == XK_Right || keycode == XK_Left)
		ft_rotate(keycode, all);
	return (0);
}

int	end(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_loop_end(vars->mlx);
	return (0);
}
