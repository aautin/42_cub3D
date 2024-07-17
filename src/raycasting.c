/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 20:02:26 by aautin            #+#    #+#             */
/*   Updated: 2024/07/09 17:26:20 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "raycasting.h"
#include "cub3D.h"
#include "map.h"
#include "utils.h"

void	ft_raycast1(t_raycasting *rc, t_objs *objs, int x)
{
	rc->hit = 0;
	rc->camerax = 2 * x / (double)objs->vars->sizex - 1;
	rc->raydirx = objs->player ->dirx + objs->player ->planex * rc->camerax;
	rc->raydiry = objs->player ->diry + objs->player ->planey * rc->camerax;
	rc->mapx = (int)objs->player ->x;
	rc->mapy = (int)objs->player ->y;
	if (rc->raydirx == 0)
		rc->deltadistx = 1e30;
	else if (rc->raydirx > 0)
		rc->deltadistx = 1 / rc->raydirx;
	else
		rc->deltadistx = -(1 / rc->raydirx);
	if (rc->raydiry == 0)
		rc->deltadisty = 1e30;
	else if (rc->raydiry > 0)
		rc->deltadisty = 1 / rc->raydiry;
	else
		rc->deltadisty = -(1 / rc->raydiry);
}

void	ft_raycast2(t_raycasting *rc, t_player *player)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (player->x - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - player->x) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (player->y - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - player->y) * rc->deltadisty;
	}
}

void	ft_raycast3(t_raycasting *rc, t_map *map)
{
	if (rc->sidedistx < rc->sidedisty)
	{
		rc->sidedistx += rc->deltadistx;
		rc->mapx += rc->stepx;
		rc->side = 0;
	}
	else
	{
		rc->sidedisty += rc->deltadisty;
		rc->mapy += rc->stepy;
		rc->side = 1;
	}
	if (map->area[rc->mapy][rc->mapx] == '1')
		rc->hit = 1;
}

void	ft_raycast4(t_raycasting *rc, t_objs *objs)
{
	if (rc->side == 1)
		rc->perpwalldist = (rc->sidedisty - rc->deltadisty);
	else
		rc->perpwalldist = (rc->sidedistx - rc->deltadistx);
	rc->lineheight = (int)(objs->vars->sizey / rc->perpwalldist);
	rc->drawstart = -rc->lineheight / 2 + objs->vars->sizey / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + objs->vars->sizey / 2;
	if (rc->drawend >= objs->vars->sizey)
		rc->drawend = objs->vars->sizey - 1;
	if (rc->side == 0)
		rc->wallx = objs->player ->y + rc->perpwalldist * rc->raydiry;
	else
		rc->wallx = objs->player ->x + rc->perpwalldist * rc->raydirx;
	rc->wallx -= floor(rc->wallx);
	rc->texture = ft_find_texture(rc->side, rc->raydirx, rc->raydiry, objs->map);
	rc->texx = (int)(rc->wallx * (double)rc->texture->width);
	if ((rc->side == 0 && rc->raydirx > 0)
		|| (rc->side == 1 && rc->raydiry < 0))
		rc->texx = rc->texture->width - rc->texx - 1;
	rc->step = 1.0 * rc->texture->height / rc->lineheight;
	rc->texpos = (rc->drawstart - objs->vars->sizey / 2 + rc->lineheight / 2)
		* rc->step;
}

void	ft_draw(t_raycasting *rc, t_objs *objs, int x)
{
	int	y;

	y = 0;
	while (y < rc->drawstart)
	{
		objs->data->addr[y * objs->vars->sizex + x] = objs->map->codes[C_INDEX - SHIFT];
		y++;
	}
	while (y < rc->drawend)
	{
		rc->texy = (int)rc->texpos & (rc->texture->height - 1);
		rc->texpos += rc->step;
		objs->data->addr[y * objs->vars->sizex
			+ x] = rc->texture->addr[rc->texture->width * rc->texy + rc->texx];
		y++;
	}
	while (y < objs->vars->sizey)
	{
		objs->data->addr[y * objs->vars->sizex + x] = objs->map->codes[F_INDEX - SHIFT];
		y++;
	}
}
