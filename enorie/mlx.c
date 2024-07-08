/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:55:01 by root              #+#    #+#             */
/*   Updated: 2024/07/08 13:55:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_rotate(double value, t_all *all)
{
	t_pos	*pos;
	double	oldplanex;
	double	olddirx;

	pos = all->pos;
	olddirx = all->pos->dirx;
	pos->dirx = pos->dirx * cos(value) - pos->diry * sin(value);
	pos->diry = olddirx * sin(value) + pos->diry * cos(value);
	oldplanex = pos->planex;
	pos->planex = pos->planex * cos(value) - pos->planey * sin(value);
	pos->planey = oldplanex * sin(value) + pos->planey * cos(value);
	ft_cubed(all);
}

int	mouse_move(t_all *all)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(all->vars->mlx, all->vars->win, &x, &y);
	if (x > all->vars->sizex / 2 + 10)
		ft_rotate(0.1, all);
	if (x < all->vars->sizex / 2 - 10)
		ft_rotate(-0.1, all);
	mlx_mouse_move(all->vars->mlx, all->vars->win,
		all->vars->sizex / 2, all->vars->sizey / 2);
	return (1);
}

int	key_hook(int keycode, t_all *all)
{
	if (keycode == XK_Escape)
		mlx_loop_end(all->vars->mlx);
	if (keycode == XK_w)
		ft_move_up(all);
	if (keycode == XK_a)
		ft_move_left(all);
	if (keycode == XK_s)
		ft_move_down(all);
	if (keycode == XK_d)
		ft_move_right(all);
	if (keycode == XK_Right)
		ft_rotate(0.05, all);
	if (keycode == XK_Left)
		ft_rotate(-0.05, all);
	return (0);
}

int	end(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}
