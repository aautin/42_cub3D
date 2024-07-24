/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:44:56 by aautin            #+#    #+#             */
/*   Updated: 2024/07/24 01:23:04 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "raycasting.h"
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
		return (FAILURE);
	}
	mlx_get_screen_size(vars->mlx, &vars->sizex, &vars->sizey);
	vars->win = mlx_new_window(vars->mlx, vars->sizex, vars->sizey, "Cub3D");
	if (vars->win == NULL)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		perror("init_vars():mlx_new_window()");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	free_vars(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free(vars);
}

int	init_objs(t_objs *objs, t_vars *vars, t_player *player, t_map *map)
{
	objs->vars = vars;
	objs->player = player;
	objs->map = map;
	objs->data = malloc(sizeof(t_data));
	objs->data->obj = mlx_new_image(objs->vars->mlx, objs->vars->sizex,
			objs->vars->sizey);
	objs->data->addr = (int *)mlx_get_data_addr(objs->data->obj,
			&objs->data->bits_pixel, &objs->data->line_length,
			&objs->data->endian);
	objs->rc = malloc(sizeof(t_raycasting));
	return (SUCCESS);
}

void	free_objs(t_objs *objs)
{
	mlx_destroy_image(objs->vars->mlx, objs->data->obj);
	free_map(objs->vars->mlx, objs->map);
	free_vars(objs->vars);
	free(objs->rc);
	free(objs->data);
	free(objs->player);
	free(objs);
}

void	ft_cub3d(t_objs *objs)
{
	int	x;

	x = 0;
	while (x < objs->vars->sizex)
	{
		ft_raycast1(objs->rc, objs, x);
		ft_raycast2(objs->rc, objs->player);
		while (objs->rc->hit == 0)
			ft_raycast3(objs->rc, objs->map);
		ft_raycast4(objs->rc, objs);
		ft_draw(objs->rc, objs, x);
		x++;
	}
	mlx_put_image_to_window(objs->vars->mlx, objs->vars->win,
		objs->data->obj, 0, 0);
}
