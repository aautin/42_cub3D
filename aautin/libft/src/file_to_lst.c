/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_lst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr >             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:26:06 by aautin            #+#    #+#             */
/*   Updated: 2024/07/08 17:41:52 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "ft_printf.h"

#define SHORT_LIMIT 32768

t_list	*file_to_lst(char *filename)
{
	t_list			*lst;
	t_list			*new;
	char			*buffer;
	unsigned int	lines_nb;
	int const		fd = open(filename, O_RDONLY);
	
	if (fd == -1)
	{
		printf("Error\nCan't open or read %s\n", filename);
		return NULL;
	}
	lst = NULL;
	lines_nb = 0;
	buffer = get_next_line(fd);
	while (buffer)
	{
		if (++lines_nb > 32768)
			printf("Too much line to read in the file, stopped at %s\n", buffer);
		new = ft_lstnew(buffer);
		if (new == NULL)
			perror("file_to_lst():ft_lstnew()");
		ft_lstadd_back(&lst, new);
		if (lines_nb > 32768 || new == NULL)
			return (close(fd), ft_lstclear(&lst, &free), NULL);
		buffer = get_next_line(fd);
	}
	close(fd);
	return (lst);
}
