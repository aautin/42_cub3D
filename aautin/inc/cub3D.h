/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 14:44:56 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 16:59:43 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "data.h"
# include "map.h"
# include "player.h"

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		sizex;
	int		sizey;
}				t_vars;

typedef struct s_objs
{
	t_map		*map;
	t_player	*player;
	t_vars		*vars;
	t_data		*data;
}				t_objs;

// t_vars
int		init_vars(t_vars *vars);
void	free_vars(t_vars *vars);

// t_objs
int		init_objs(t_objs *objs, t_vars *vars, t_player *player, t_map *map);
void	free_objs(t_objs *objs);

#endif