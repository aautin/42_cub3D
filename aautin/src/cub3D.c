/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:44:56 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 17:00:03 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#include "player.h"
#include "map.h"
#include "mlx.h"
#include "cub3D.h"

int	init_vars(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (vars->mlx == NULL)
	{
		perror("init_vars():mlx_init()");
		return FAILURE;
	}
	mlx_get_screen_size(vars->mlx, &vars->sizex, &vars->sizey);
	vars->win = mlx_new_window(vars->mlx, vars->sizex, vars->sizey, "Cub3D");
	if (vars->win == NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		perror("init_vars():mlx_new_window()");
		return FAILURE;
	}
	return SUCCESS;
}

void	free_vars(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

int	init_objs(t_objs *objs, t_vars *vars, t_player *player, t_map *map)
{
	objs->vars = vars;
	objs->player = player;
	objs->map = map;
	return SUCCESS;
}

void	free_objs(t_objs *objs)
{
	free_map(objs->vars->mlx, objs->map);
	free_vars(objs->vars);
}
