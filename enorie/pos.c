/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:54:25 by root              #+#    #+#             */
/*   Updated: 2024/06/26 16:09:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_get_pos(char **map, int i, int j, t_pos *pos)
{
	if (map[i][j] == 'N')
		ft_get_dir_n(pos);
	if (map[i][j] == 'W')
		ft_get_dir_w(pos);
	if (map[i][j] == 'E')
		ft_get_dir_e(pos);
	if (map[i][j] == 'S')
		ft_get_dir_s(pos);
}

void	ft_get_dir_n(t_pos *pos)
{
	pos->dirx = 0;
	pos->diry = -1;
	pos->planex = 0.66;
	pos->planey = 0;
}

void	ft_get_dir_s(t_pos *pos)
{
	pos->dirx = 0;
	pos->diry = 1;
	pos->planex = -0.66;
	pos->planey = 0;
}

void	ft_get_dir_w(t_pos *pos)
{
	pos->dirx = -1;
	pos->diry = 0;
	pos->planex = 0;
	pos->planey = -0.66;
}

void	ft_get_dir_e(t_pos *pos)
{
	pos->dirx = 1;
	pos->diry = 0;
	pos->planex = 0;
	pos->planey = 0.66;
}
