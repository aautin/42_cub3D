/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsttostr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:28:48 by aautin            #+#    #+#             */
/*   Updated: 2024/06/19 19:17:58 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "../includes/libft.h"

char	*lsttostr(t_list *lst)
{
	t_list	*head;
	size_t	result_size;
	char	*result;

	head = lst;
	result_size = 1;
	while (lst != NULL)
	{
		result_size += ft_strlen(lst->content);
		lst = lst->next;
	}
	result = ft_calloc(result_size, sizeof(char));
	if (result == NULL)
	{
		perror("lsttostr():ft_calloc()");
		return (NULL);
	}
	lst = head;
	while (lst != NULL)
	{
		ft_strlcat(result, lst->content, result_size);
		lst = lst->next;
	}
	return (result);
}
