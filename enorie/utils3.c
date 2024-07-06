/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:06:14 by root              #+#    #+#             */
/*   Updated: 2024/07/02 21:25:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_puterror(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	return (1);
}

int	ft_init_map(t_map *map)
{
	map->ea = malloc(sizeof(t_data));
	if (!map->ea)
		return (1);
	map->no = malloc(sizeof(t_data));
	if (!map->no)
		return (free(map->ea), 1);
	map->we = malloc(sizeof(t_data));
	if (!map->we)
		return (free(map->no), free(map->ea), 1);
	map->so = malloc(sizeof(t_data));
	if (!map->so)
		return (free(map->we), free(map->no), free(map->ea), 1);
	map->map = NULL;
	return (0);
}

t_all	*ft_init_strucks(void)
{
	t_all		*all;

	all = malloc(sizeof(t_all));
	if (!all)
		return (NULL);
	all->map = malloc(sizeof(t_map));
	if (!all->map)
		return (free(all), NULL);
	all->pos = malloc(sizeof(t_pos));
	if (!all->pos)
		return (free(all->map), free(all), NULL);
	all->rc = malloc(sizeof(t_raycast));
	if (!all->rc)
		return (free(all->map), free(all->pos), free(all), NULL);
	all->vars = malloc(sizeof(t_vars));
	if (!all->vars)
		return (free(all->rc), free(all->map), free(all->pos), free(all), NULL);
	all->data = malloc(sizeof(t_data));
	if (!all->data)
		return (free(all->vars), free(all->rc), free(all->map),
			free(all->pos), free(all), NULL);
	if (ft_init_map(all->map))
		return (free(all->data), free(all->vars), free(all->rc), free(all->map),
			free(all->pos), free(all), NULL);
	return (all);
}
