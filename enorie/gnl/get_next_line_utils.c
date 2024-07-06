/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enorie <enorie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:57:01 by enorie            #+#    #+#             */
/*   Updated: 2024/01/10 17:17:06 by enorie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checkstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*r;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	r = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!r)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			r[j++] = s1[i++];
	i = 0;
	while (s2[i])
		r[j++] = s2[i++];
	r[j] = '\0';
	if (s1 && s1[0])
		free(s1);
	return (r);
}
