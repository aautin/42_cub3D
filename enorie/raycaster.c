/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:21:52 by root              #+#    #+#             */
/*   Updated: 2024/07/03 16:26:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_raycast1(t_raycast *rc, t_all *all, int x)
{
	rc->hit = 0;
	rc->camerax = 2 * x / (double)all->vars->sizex - 1;
	rc->raydirx = all->pos->dirx + all->pos->planex * rc->camerax;
	rc->raydiry = all->pos->diry + all->pos->planey * rc->camerax;
	rc->mapx = (int)all->pos->x;
	rc->mapy = (int)all->pos->y;
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

void	ft_raycast2(t_raycast *rc, t_pos *pos)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (pos->x - rc->mapx) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->mapx + 1.0 - pos->x) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (pos->y - rc->mapy) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->mapy + 1.0 - pos->y) * rc->deltadisty;
	}
}

void	ft_raycast3(t_raycast *rc, t_map *map)
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
	if (map->map[rc->mapy][rc->mapx] == '1')
		rc->hit = 1;
}

void	ft_raycast4(t_raycast *rc, t_all *all)
{
	if (rc->side == 1)
		rc->perpwalldist = (rc->sidedisty - rc->deltadisty);
	else
		rc->perpwalldist = (rc->sidedistx - rc->deltadistx);
	rc->lineheight = (int)(all->vars->sizey / rc->perpwalldist);
	rc->drawstart = -rc->lineheight / 2 + all->vars->sizey / 2;
	if (rc->drawstart < 0)
		rc->drawstart = 0;
	rc->drawend = rc->lineheight / 2 + all->vars->sizey / 2;
	if (rc->drawend >= all->vars->sizey)
		rc->drawend = all->vars->sizey - 1;
	if (rc->side == 0)
		rc->wallx = all->pos->y + rc->perpwalldist * rc->raydiry;
	else
		rc->wallx = all->pos->x + rc->perpwalldist * rc->raydirx;
	rc->wallx -= floor(rc->wallx);
	rc->texture = ft_find_texture(rc->side, rc->raydirx, rc->raydiry, all->map);
	rc->texx = (int)(rc->wallx * (double)rc->texture->width);
	if ((rc->side == 0 && rc->raydirx > 0)
		|| (rc->side == 1 && rc->raydiry < 0))
		rc->texx = rc->texture->width - rc->texx - 1;
	rc->step = 1.0 * rc->texture->height / rc->lineheight;
	rc->texpos = (rc->drawstart - all->vars->sizey / 2 + rc->lineheight / 2)
		* rc->step;
}

void	ft_draw(t_raycast *rc, t_all *all, int x)
{
	int	y;

	y = 0;
	while (y < rc->drawstart)
	{
		all->data->addr[y * all->vars->sizex + x] = all->map->c;
		y++;
	}
	while (y < rc->drawend)
	{
		rc->texy = (int)rc->texpos & (rc->texture->height - 1);
		rc->texpos += rc->step;
		all->data->addr[y * all->vars->sizex
			+ x] = rc->texture->addr[rc->texture->width * rc->texy + rc->texx];
		y++;
	}
	while (y < all->vars->sizey)
	{
		all->data->addr[y * all->vars->sizex + x] = all->map->f;
		y++;
	}
}
