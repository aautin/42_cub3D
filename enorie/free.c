/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:04:07 by root              #+#    #+#             */
/*   Updated: 2024/07/08 12:40:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_free_numbers(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i])
		free(numbers[i++]);
	free(numbers);
}

void	ft_free_img(t_vars *vars, t_data *img)
{
	if (img->img)
		mlx_destroy_image(vars->mlx, img->img);
	free(img);
}

void	ft_free_map(t_all *all)
{
	if (all->map->ea)
		ft_free_img(all->vars, all->map->ea);
	if (all->map->no)
		ft_free_img(all->vars, all->map->no);
	if (all->map->so)
		ft_free_img(all->vars, all->map->so);
	if (all->map->we)
		ft_free_img(all->vars, all->map->we);
	if (all->map->map)
		ft_free_numbers(all->map->map);
}

void	ft_free_all(t_all *all)
{
	if (all->vars->win)
		mlx_destroy_window(all->vars->mlx, all->vars->win);
	ft_free_map(all);
	if (all->pos)
		free(all->pos);
	if (all->vars->mlx)
	{
		mlx_destroy_display(all->vars->mlx);
		free(all->vars->mlx);
	}
	if (all->rc)
		free(all->rc);
	if (all->vars)
		free(all->vars);
	if (all->data)
		free(all->data);
	if (all->map)
		free(all->map);
	if (all)
		free(all);
}
