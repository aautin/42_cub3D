/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:56:34 by enorie            #+#    #+#             */
/*   Updated: 2024/01/16 15:39:01 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		checkstr(char *str);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_fill_str(int fd, char *rstr);
char	*ft_trim(char *rstr);
void	ft_whats_left(char *rstr, char *reste);
char	*get_next_line(int fd);

#endif
