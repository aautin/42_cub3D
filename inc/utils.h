/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:25:14 by aautin            #+#    #+#             */
/*   Updated: 2024/07/27 16:57:00 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "data.h"
# include "map.h"

int		index_to_status(int index);
t_data	*ft_find_texture(int side, double raydirx, double raydiry, t_map *map);
int		check_lines_lenght(int *xsize, int sizetab);

#endif