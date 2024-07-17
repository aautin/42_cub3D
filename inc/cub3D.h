/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:44:56 by aautin            #+#    #+#             */
/*   Updated: 2024/07/09 17:17:26 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define XK_MISCELLANY
# define XK_LATIN1

# include <X11/X.h>
# include <X11/keysymdef.h>

# include "data.h"
# include "map.h"
# include "raycasting.h"
# include "player.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		sizex;
	int		sizey;
}	t_vars;

typedef struct s_objs
{
	t_map			*map;
	t_player		*player;
	t_vars			*vars;
	t_data			*data;
	t_raycasting	*rc;
}	t_objs;

void	ft_cub3d(t_objs *objs);

// hook.c
void	init_hooks(t_objs *objs);

// t_vars
int		init_vars(t_vars *vars);
void	free_vars(t_vars *vars);

// t_objs
int		init_objs(t_objs *objs, t_vars *vars, t_player *player, t_map *map);
void	free_objs(t_objs *objs);

// raycasting.h
void	ft_raycast1(t_raycasting *rc, t_objs *objs, int x);
void	ft_raycast2(t_raycasting *rc, t_player *pos);
void	ft_raycast3(t_raycasting *rc, t_map *map);
void	ft_raycast4(t_raycasting *rc, t_objs *objs);
void	ft_draw(t_raycasting *rc, t_objs *objs, int x);

#endif