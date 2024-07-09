/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 19:23:57 by aautin            #+#    #+#             */
/*   Updated: 2024/07/09 19:57:50 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "cub3D.h"
#include "mlx.h"
#include "move.h"

static int	mouse_move(t_objs *objs)
{
	int	x;
	int	y;

	mlx_mouse_get_pos(objs->vars->mlx, objs->vars->win, &x, &y);
	if (x > objs->vars->sizex / 2 + 10)
		ft_rotate(0.1, objs);
	if (x < objs->vars->sizex / 2 - 10)
		ft_rotate(-0.1, objs);
	mlx_mouse_move(objs->vars->mlx, objs->vars->win,
		objs->vars->sizex / 2, objs->vars->sizey / 2);
	return (1);
}

static int	key_press(int keycode, t_objs *objs)
{
	if (keycode == XK_Escape)
		mlx_loop_end(objs->vars->mlx);
	if (keycode == XK_w)
		ft_move_up(objs);
	if (keycode == XK_a)
		ft_move_left(objs);
	if (keycode == XK_s)
		ft_move_down(objs);
	if (keycode == XK_d)
		ft_move_right(objs);
	if (keycode == XK_Right)
		ft_rotate(0.05, objs);
	if (keycode == XK_Left)
		ft_rotate(-0.05, objs);
	return (0);
}

static int	cross_button(t_vars *vars)
{
	mlx_loop_end(vars->mlx);
	return (0);
}

void	init_hooks(t_objs *objs)
{
	mlx_hook(objs->vars->win, 2, 1L << 0, &key_press, objs);
	mlx_hook(objs->vars->win, 17, 0, &cross_button, objs->vars);
	mlx_loop_hook(objs->vars->mlx, &mouse_move, objs);
}
