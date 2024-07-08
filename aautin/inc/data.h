/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:19:05 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 14:23:21 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_data
{
	void	*obj;
	int		*addr;
	int		bits_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_data;

#endif